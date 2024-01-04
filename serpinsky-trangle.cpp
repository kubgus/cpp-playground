#include <iostream>

void printSerp(int n) {
    for (int y = n - 1; y >= 0; y--) {
    	for (int s = 0; s < y; s++) std::cout << "  ";
    	for (int x = 0; x + y < n; x++) std::cout << ((x & y) ? "  " : "# ");
    	std::cout << "\n";
    }
}

int main()
{
    int n;
    std::cin >> n;
    printSerp(n);
    return 0;
}
