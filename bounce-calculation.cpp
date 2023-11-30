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
    // x: position
    double x;
    // v: velocity [m/s]
    double v;
    // m: mass [kg]
    long double m;

    constexpr Point(double x, double v, long double m) : x(x), v(v), m(m) {}
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
    Point left(1, 0, 1);
    Point right(left.x, -1, argc > 1 ? pow(100, std::stold(argv[1])) : 1);
    // b: bounces
    int b = 0;
    while (left.v < 0 || left.v > right.v)
    {
        LOG("... " << b);
        double r = (left.x - right.x) / (left.v - right.v);
        left.x += left.v * r;
        right.x += right.v * r;
        double m = left.m + right.m;
        double vl = (2 * right.m * right.v + (left.m - right.m) * left.v) / m;
        double vr = (2 * left.m * left.v + (right.m - left.m) * right.v) / m;
        left.v = vl;
        right.v = vr;
        b++;
        if (left.v < 0)
        {
            double r = left.x / left.v;
            left.x += left.v * r;
            right.x += right.v * r;
            left.v = -left.v;
            b++;
        }
    }
    std::cout << "PI: " << b << "\n";
}