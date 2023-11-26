#include <iostream>
#include <stack>

bool isValid(const char *string)
{
    std::stack<char> storage;
    for (int i = 0; string[i] != '\0'; i++)
    {
        switch (string[i])
        {
        case '(':
        case '{':
        case '[':
            storage.push(string[i]);
            break;
        case ')':
            if (storage.top() == '(')
                storage.pop();
            else
                return false;
            break;
        case '}':
            if (storage.top() == '{')
                storage.pop();
            else
                return false;
            break;
        case ']':
            if (storage.top() == '[')
                storage.pop();
            else
                return false;
            break;
        default:
            return false;
        }
    }
    if (storage.empty())
        return true;
    return false;
}

int main()
{
    std::cout << isValid("()") << std::endl;
}