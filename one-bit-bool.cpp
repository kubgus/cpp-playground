#include <bitset>
#include <iostream>

template <int N>
using ob_bool = std::bitset<N>;

int main() {
    ob_bool<8> boolean;
    boolean.set(2, true);
    std::cout << boolean << std::endl;
}
