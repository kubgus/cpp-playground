#include <iostream>
#include <cmath>
#include <cstring>

struct Point
{
    // [position] = m
    double x;
    // [velocity] = ms^-1
    double v;
    // [mass] = kg
    long long m;

    Point(double x, double v, long double m) : x(x), v(v), m(m) {}
};

inline void print(const long long &t, const int &b, const Point &left, const Point &right)
{
    long y = t / 31536000, m = (t % 31536000) / 2592000, d = (t % 2592000) / 86400, h = (t % 86400) / 3600, min = (t % 3600) / 60, s = t % 60;
    std::cout << "Time: " << y << "y " << m << "m " << d << "d " << h << "h " << min << "min " << s << "s" << std::endl
              << "Bounces: " << b << std::endl
              << "Left: " << left.x << "m, " << left.v << "ms^-1" << std::endl
              << "Right: " << right.x << "m, " << right.v << "ms^-1" << std::endl
              << std::endl;
}

int main(int argc, char **argv)
{
    Point left(1, 0, 1);
    Point right(2, -1, 100000000);

    // [time] = s
    long long t = 0;
    // [bounces]
    int b = 0;

    while (left.v < 0 || left.v > right.v)
    {
        left.x += left.v;
        right.x += right.v;
        if (left.x <= 0)
        {
            left.x = 0;
            left.v = -left.v;
            b++;
        }
        if (left.x >= right.x)
        {
            right.x = left.x;

            double m = left.m + right.m;
            double vl = (2 * right.m * right.v + (left.m - right.m) * left.v) / m;
            double vr = (2 * left.m * left.v + (right.m - left.m) * right.v) / m;

            left.v = vl;
            right.v = vr;

            b++;
        }
        if (t % 1000000000 == 0)
            print(t, b, left, right);
        t++;
    }

    std::cout << "===================================" << std::endl
              << std::endl;
    print(t, b, left, right);
}