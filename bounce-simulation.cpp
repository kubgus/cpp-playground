#include <iostream>

struct Point
{
    // x: position [m]
    double x;
    // v: velocity [m/s]
    double v;
    // m: mass [kg]
    long double m;

    constexpr Point(double x, double v, long double m) : x(x), v(v), m(m) {}

    inline const double p()
    {
        return m * v;
    }
};

inline void print(long long t, int b, const Point &left, const Point &right)
{
    long y = t / 31536000, m = (t % 31536000) / 2592000, d = (t % 2592000) / 86400, h = (t % 86400) / 3600, min = (t % 3600) / 60, s = t % 60;
    std::cout << "Time: " << y << "y " << m << "m " << d << "d " << h << "h " << min << "min " << s << "s\n"
              << "Bounces: " << b << "\n"
              << "Left: " << left.x << "m, " << left.v << "m/s\n"
              << "Right: " << right.x << "m, " << right.v << "m/s\n\n";
}

int main()
{
    Point left(1, 0, 1);
    Point right(2, -1, 100000000);

    // t: time [s]
    long long t = 0;
    // b: bounces
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
            double vl = (2 * right.p() + (left.m - right.m) * left.v) / m;
            double vr = (2 * left.p() + (right.m - left.m) * right.v) / m;

            left.v = vl;
            right.v = vr;

            b++;
        }

        if (t % 1000000000 == 0)
            print(t, b, left, right);

        t++;
    }

    std::cout << "===================================\n\n";
    print(t, b, left, right);
}