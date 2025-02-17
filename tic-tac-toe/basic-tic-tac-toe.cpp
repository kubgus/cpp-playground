#include <iostream>

#define CIN_RESET()   \
    std::cin.clear(); \
    std::cin.ignore(256, '\n');

char player = 'X';
int turn = 0;
char board[9] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9'};

void PrintBoard(const char *const board)
{
    std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n"
              << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n"
              << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n";
}

void HandlePlayerInput(const char &current, char *board)
{
    int choice;
    std::cout << "Pick a spot to place " << current << ": ";
    std::cin >> choice;
    if (board[choice - 1] == 'X' || board[choice - 1] == 'O' || choice < 1 || choice > 9 || std::cin.fail())
    {
        CIN_RESET();
        std::cout << "Spot taken or non-existant! Try again!\n";
        HandlePlayerInput(current, board);
        return;
    }
    board[choice - 1] = current;
}

template <typename T>
inline bool ThreeEqual(T st, T nd, T rd)
{
    return st == nd && nd == rd;
}

inline void SwitchPlayer(char &current)
{
    current = current == 'X' ? 'O' : 'X';
}

int main()
{
    PrintBoard(board);
    while (turn < 9)
    {
        turn++;
        HandlePlayerInput(player, board);
        PrintBoard(board);
        if (ThreeEqual(board[0], board[1], board[2]) || ThreeEqual(board[3], board[4], board[5]) || ThreeEqual(board[6], board[7], board[8]) ||
            ThreeEqual(board[0], board[3], board[6]) || ThreeEqual(board[1], board[4], board[7]) || ThreeEqual(board[2], board[5], board[8]) ||
            ThreeEqual(board[0], board[4], board[8]) || ThreeEqual(board[2], board[4], board[6]))
        {
            std::cout << "Player " << player << " won the game!\n";
            CIN_RESET();
            std::cin.get();
            return 0;
        }
        SwitchPlayer(player);
    }
    std::cout << "It's a tie!\n";
    CIN_RESET();
    std::cin.get();
    return 0;
}