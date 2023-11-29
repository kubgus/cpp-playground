#include <iostream>
#include <cmath>

long long int returnLargeInt()
{
    return 1694207819321;
}

const int M = 1000000007;

int main()
{
    std::cout << returnLargeInt() % M << std::endl;
}