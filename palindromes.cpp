#include <iostream>
#include <cstring>
#include <cmath>

bool isPalindrome(const char *string)
{
    int len = strlen(string);
    for (int i = 0; i < floor(len / 2); i++)
    {
        if (string[i] != string[len - i - 1])
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    std::cout << argv[1] << ' ' << (isPalindrome(argv[1]) ? "is a palindrome!" : "isn't a palindrome!") << std::endl;
}