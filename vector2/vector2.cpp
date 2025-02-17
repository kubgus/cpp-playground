#include "vector2.h"

#include <cmath>
#include <cstdlib>

vector2::vector2(float x, float y) : x(x), y(y) {}

vector2 vector2::zero() {
    return vector2(0, 0);
}
vector2 vector2::from_angle(float angle) {
    return vector2(std::cos(angle), std::sin(angle));
}

vector2 vector2::operator+(const vector2& other) const {
    return vector2(x + other.x, y + other.y);
}

void vector2::operator+=(const vector2& other) {
    x += other.x;
    y += other.y;
}

vector2 vector2::operator-(const vector2& other) const {
    return vector2(x - other.x, y - other.y);
}

void vector2::operator-=(const vector2& other) {
    x -= other.x;
    y -= other.y;
}

vector2 vector2::operator-() const {
    return vector2(-x, -y);
}

vector2 operator*(const vector2& v, float s) {
    return vector2(v.x * s, v.y * s);
}

inline float vector2::abs() const {
    return std::sqrt(x * x + y * y);
}

inline float vector2::angle() const {
    return std::atan2(y, x);
}

vector2 vector2::normalize() const {
    float len = abs();
    return vector2(x / len, y / len);
}
