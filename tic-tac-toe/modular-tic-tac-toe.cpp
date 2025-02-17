#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#define CIN_RESET()   \
    std::cin.clear(); \
    std::cin.ignore(256, '\n');

const int BOARD_SIZE = 3;

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    RESET
};

inline std::string ansi_color(Color color) {
    switch (color) {
        case RED:     return "\033[31m";
        case GREEN:   return "\033[32m";
        case BLUE:    return "\033[34m";
        case YELLOW:  return "\033[33m";
        case CYAN:    return "\033[36m";
        case MAGENTA: return "\033[35m";
        case RESET:   return "\033[0m";
        default:      return "\033[0m";
    }
}

inline std::string format(std::string text, Color color, int width = 0) {
    std::stringstream ss;
    ss << ansi_color(color) << std::setw(width) << text << ansi_color(RESET);
    return ss.str();
}

template <typename T>
T take_validated_input(
    std::string prompt,
    std::function<bool(T)> validate = [](T){ return true; },
    std::string error_msg = "Unexpected input!"
) {
    T variable;

    while (true) {
        std::cout << prompt << " ";
        std::cin >> variable;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << format("Invalid input! Try again!", RED) << std::endl;
        } else if (!validate(variable)) {
            std::cout << format(error_msg + " Try again!", RED) << std::endl;
        } else break;
    }

    return variable;
}

enum TileState { EMPTY = 0, X, O };

std::string tile_to_string(TileState state, int width = 0) {
    switch (state) {
        case X:     return format("X", CYAN, width);
        case O:     return format("O", MAGENTA, width);
        default:    return " ";
    }
}

enum GameState { UNFINISHED, X_WON, O_WON, DRAW };

std::string game_state_to_string(GameState state) {
    switch (state) {
        case X_WON: return tile_to_string(X) + " won!";
        case O_WON: return tile_to_string(O) + " won!";
        case DRAW:  return "Draw!";
        default:    return "Unfinished! (how?)";
    }
}

struct Board {
    TileState tiles[BOARD_SIZE][BOARD_SIZE];

    Board() {
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                tiles[y][x] = EMPTY;
            }
        }
    }

    inline TileState get(int x, int y) const { return tiles[y][x]; }

    inline bool is_empty(int x, int y) {
        return tiles[y][x] == EMPTY;
    }

    inline bool set(int x, int y, TileState state) {
        if (is_empty(x, y)) {
            tiles[y][x] = state;
            return true;
        }
        return false;
    }

    void print() const {
        int max_digits = std::to_string(BOARD_SIZE * BOARD_SIZE).size();
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (tiles[y][x] == EMPTY) {
                    int tileNumber = y * BOARD_SIZE + x + 1;
                    std::cout
                        << std::setw(max_digits)
                        << tileNumber
                        << " ";
                } else {
                    std::cout
                        << tile_to_string(tiles[y][x], max_digits)
                        << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    GameState eval() const {
        // Check rows and columns for a win
        for (int i = 0; i < BOARD_SIZE; i++) {
            // Check row
            if (tiles[i][0] != EMPTY) {
                bool rowWin = true;
                for (int j = 1; j < BOARD_SIZE; j++) {
                    if (tiles[i][j] != tiles[i][0]) {
                        rowWin = false;
                        break;
                    }
                }
                if (rowWin) return (tiles[i][0] == X) ? X_WON : O_WON;
            }

            // Check column
            if (tiles[0][i] != EMPTY) {
                bool colWin = true;
                for (int j = 1; j < BOARD_SIZE; j++) {
                    if (tiles[j][i] != tiles[0][i]) {
                        colWin = false;
                        break;
                    }
                }
                if (colWin) return (tiles[0][i] == X) ? X_WON : O_WON;
            }
        }

        // Check main diagonal
        if (tiles[0][0] != EMPTY) {
            bool mainDiagWin = true;
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (tiles[i][i] != tiles[0][0]) {
                    mainDiagWin = false;
                    break;
                }
            }
            if (mainDiagWin) return (tiles[0][0] == X) ? X_WON : O_WON;
        }

        // Check anti-diagonal
        if (tiles[0][BOARD_SIZE - 1] != EMPTY) {
            bool antiDiagWin = true;
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (tiles[i][BOARD_SIZE - 1 - i] != tiles[0][BOARD_SIZE - 1]) {
                    antiDiagWin = false;
                    break;
                }
            }
            if (antiDiagWin) return (tiles[0][BOARD_SIZE - 1] == X) ? X_WON : O_WON;
        }

        // Check if the board is full (Draw)
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (tiles[y][x] == EMPTY) {
                    return UNFINISHED; // The game is still ongoing
                }
            }
        }

        return DRAW; // If no empty tiles and no winner, it's a draw
    }

};

struct Agent {
    TileState team;

    Agent(TileState team) : team(team) {}

    virtual bool place_tile(Board& board) const = 0;
};

struct Player : public Agent {
    Player(TileState team) : Agent(team) {}

    bool place_tile(Board& board) const override {
        int index = get_input() - 1;
        int x = index % BOARD_SIZE;
        int y = index / BOARD_SIZE;
        bool placed = board.set(x, y, team);
        if (!placed) {
            CIN_RESET();
            std::cout << format("Spot already taken! Try again!\n", RED);
            return place_tile(board);
        }
        return placed;
    }

    int get_input() const {
        std::string prompt = "Pick a spot to place " + tile_to_string(team) + ": ";
        int choice = take_validated_input<int>(
            prompt,
            [](int x) { return x > 0 && x <= BOARD_SIZE * BOARD_SIZE; },
            "Spot does not exist!"
        );
        return choice;
    }
};

struct DumbAI : public Agent {
    DumbAI(TileState team) : Agent(team) {}

    bool place_tile(Board& board) const override {
        int index = std::rand() % (BOARD_SIZE * BOARD_SIZE);
        int x = index % BOARD_SIZE;
        int y = index / BOARD_SIZE;
        bool placed = board.set(x, y, team);
        if (!placed) {
            return place_tile(board);
        }
        std::cout << "AI places "
            << tile_to_string(team)
            << " at "
            << y * BOARD_SIZE + x + 1
            << "...\n";
        return placed;
    }
};

int main() {
    std::srand(std::time(nullptr));

    // Instantiate agents
    Player player(X);
    DumbAI ai(O);

    Board board;
    // Cast agents to general interface type
    Agent& agent1 = player;
    Agent& agent2 = ai;

    std::cout << format("Tic tac toe!\n\n", YELLOW);
    while (board.eval() == UNFINISHED) {
        board.print();
        agent1.place_tile(board);
        if (board.eval() != UNFINISHED) {
            break;
        }
        board.print();
        agent2.place_tile(board);
    }
    board.print();
    std::cout << "Game over!\n";

    std::cout << game_state_to_string(board.eval()) << "\n";
    return 0;
}
