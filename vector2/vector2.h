class vector2 {
public:
    float x, y;

    vector2(float x, float y);

    static vector2 zero();
    static vector2 from_angle(float angle);

    vector2 operator+(const vector2& other) const;
    void operator+=(const vector2& other);
    vector2 operator-(const vector2& other) const;
    void operator-=(const vector2& other);
    vector2 operator-() const;
    friend vector2 operator*(const vector2& v, float s);

    inline float abs() const;
    inline float angle() const;

    vector2 normalize() const;
};
