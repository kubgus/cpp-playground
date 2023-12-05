#include <iomanip>
#include <iostream>
#include <string>

#ifdef BC_LOG
#define LOG(x) std::cout << x << "\n"
#else
#define LOG(x)
#endif

struct Point
{
    // v: velocity [m/s]
    double v;
    // m: mass [kg]
    long double m;

    constexpr Point(double v, long double m) : v(v), m(m) {}
};

constexpr double pow(double x, int n)
{
    double r = 1;
    for (int i = 0; i < n; i++)
        r *= x;
    return r;
}

int main(int argc, char **argv)
{
    Point left(0, 1);
    Point right(-1, argc > 1 ? pow(100, std::stold(argv[1])) : 1);
    double m = left.m + right.m;
    // b: bounces
    int b = 0;
    while (left.v < 0 || left.v > right.v)
    {
        LOG("... " << b);
        double vl = (2 * right.m * right.v + (left.m - right.m) * left.v) / m;
        double vr = (2 * left.m * left.v + (right.m - left.m) * right.v) / m;
        if (vl < 0)
            b++;
        left.v = vl < 0 ? -vl : vl;
        right.v = vr;
        b++;
    }
    std::cout << "PI: " << (b % 2 == 0 ? b - 1 : b) << "\n";
}