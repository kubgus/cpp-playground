#include <iostream>

bool isPrime(int x)
{
    for (int i = x - 1; i > 1; i--)
        if (x % i == 0)
            return false;
    return true;
}

int main(int argc, char **argv)
{
    std::cout << argv[1] << " is" << (!isPrime(atoi(argv[1])) ? " not " : " ") << "a prime number!" << std::endl;
}