#include <iostream>
#include <cstdlib>
#include <time.h>

int random(int max)
{
    srand(time(0));
    return rand() % max;
}

int main()
{
    int answer = random(10000);

    int turnLim = 15;
    int turn = 0;

    int input;
    do
    {
        std::cout << "Guess " << turn + 1 << ": ";
        std::cin >> input;
        if (input == answer)
        {
            std::cout << "Victory!" << std::endl;
            return 1;
        }
        std::cout << (input < answer ? "The number is higher!" : "The number is lower!") << std::endl;
        turn++;
    } while (turn < turnLim);
    std::cout << "You lost! The correct number was " << answer << "..." << std::endl;
}