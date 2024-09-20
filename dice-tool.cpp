#include <cstdint>
#include <iostream>
#include <vector>

// Algorithm and CLI for calculating dice probabilities for any amount
// of dice with any amount of respectful sides.
// This code was written without using external sources to test
// my knowledge of C++ and algorithms.
// May be faulty - edge cases not tested yet!

struct dice {
    uint32_t sides = 6;
};

uint32_t total_outcome_count(std::vector<dice> dice_set) {
    int count = 1;
    for (dice d : dice_set) {
        count *= d.sides;
    }
    return count;
}

uint32_t good_outcome_count(
    const std::vector<dice>& dice_set, int aim,
    int value_until_now = 0, int index = 0
) {
    dice d1 = dice_set[index];
    if (index + 1 > dice_set.size()) {
        return d1.sides <= aim ? 1 : 0;
    }
    dice d2 = dice_set[index + 1];
    int count = 0;
    for (int i = 1; i <= d1.sides; i++) {
        if (aim - (value_until_now + i) <= d2.sides) {
            count += good_outcome_count(
                dice_set, aim, value_until_now + i, index + 1
            );
        }
    }
    return count;
}

inline float chance_of(std::vector<dice> dice_set, int number) {
    uint32_t total_outcomes = total_outcome_count(dice_set);
    uint32_t good_outcomes = good_outcome_count(dice_set, number);
    return (float)good_outcomes / (float)total_outcomes;
}

inline float to_percent(float number) {
    return number * 100;
}

int main() {
    std::cout << "Number of dice: ";
    uint32_t dice_amt;
    std::cin >> dice_amt;

    std::vector<dice> dice_set;
    dice_set.reserve(dice_amt);

    for (int i = 0; i < dice_amt; i++) {
        std::cout << "Sides of D" << i + 1 << ": ";
        uint32_t sides;
        std::cin >> sides;

        dice_set.push_back(dice { sides });
    }

    // use for loop for scope safety istead of while
    for (bool is_running = true; is_running;) {
        std::cout << "Enter desired amount ('-1' to quit): ";
        int aim;
        std::cin >> aim;

        if (aim < 0) {
            is_running = false;
        }

        float chance = chance_of(dice_set, aim);
        std::cout << "Chance: " << to_percent(chance) << "%" << std::endl;
    }

    std::cout << "Bye!" << std::endl;

}
