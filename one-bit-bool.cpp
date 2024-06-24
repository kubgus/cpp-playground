#include <cstdint>
#include <iostream>

#define ASSERT(x, s) if (!(x)) { std::cout << s << "\n"; }

constexpr std::uint8_t bit_1 = 0b00000001;
constexpr std::uint8_t bit_2 = 0b00000010;
constexpr std::uint8_t bit_3 = 0b00000100;
constexpr std::uint8_t bit_4 = 0b00001000;
constexpr std::uint8_t bit_5 = 0b00010000;
constexpr std::uint8_t bit_6 = 0b00100000;
constexpr std::uint8_t bit_7 = 0b01000000;
constexpr std::uint8_t bit_8 = 0b10000000;

struct one_bit_bool {
public:
    one_bit_bool(std::uint8_t x) : _x(x) {}
    one_bit_bool(bool x) : _x(x ? bit_1 : 0) {}
    one_bit_bool() : _x(0) {}

    one_bit_bool& operator=(bool x) {
        _x |= bit_1 << !x;
        return *this;
    }

    inline bool get_1() const { return _x & bit_1; }
    inline bool get_2() const { return _x & bit_2; }
    inline bool get_3() const { return _x & bit_3; }
    inline bool get_4() const { return _x & bit_4; }
    inline bool get_5() const { return _x & bit_5; }
    inline bool get_6() const { return _x & bit_6; }
    inline bool get_7() const { return _x & bit_7; }
    inline bool get_8() const { return _x & bit_8; }

    operator bool() const { return get_1(); }

    inline void set_1(bool x) { _x |= bit_1 << !x; }
    inline void set_2(bool x) { _x |= bit_2 << !x; }
    inline void set_3(bool x) { _x |= bit_3 << !x; }
    inline void set_4(bool x) { _x |= bit_4 << !x; }
    inline void set_5(bool x) { _x |= bit_5 << !x; }
    inline void set_6(bool x) { _x |= bit_6 << !x; }
    inline void set_7(bool x) { _x |= bit_7 << !x; }
    inline void set_8(bool x) { _x |= bit_8 << !x; }
private:
    std::uint8_t _x;
};

int main() {
    one_bit_bool b;
    b.set_1(false);
    b.set_2(true);
    b.set_3(false);
    b.set_4(true);
    b.set_5(false);
    b.set_6(true);
    b.set_7(false);
    b.set_8(true);

    ASSERT(!b.get_1(), "First bit failed" << b.get_1());
    ASSERT(b.get_2(), "Second bit failed" << b.get_2());
    ASSERT(!b.get_3(), "Third bit failed" << b.get_3());
    ASSERT(b.get_4(), "Fourth bit failed" << b.get_4());
    ASSERT(!b.get_5(), "Fifth bit failed" << b.get_5());
    ASSERT(b.get_6(), "Sixth bit failed" << b.get_6());
    ASSERT(!b.get_7(), "Seventh bit failed" << b.get_7());
    ASSERT(b.get_8(), "Eighth bit failed" << b.get_8());

    if (b.get_4()) {
        std::cout << "This should happen" << std::endl;
    }

    if (b.get_7()) {
        std::cout << "This should not happen" << std::endl;
    }

    return 0;
}
