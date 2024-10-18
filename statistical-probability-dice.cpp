#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

#define LOG(x) std::cout << x << "\n"

constexpr int sides = 6;
using sides_array = std::array<std::atomic<int>, sides>;

void simulate_dice_rolls(int rolls, sides_array& result, unsigned int seed) {
    std::array<int, sides> local_result = {0};
    std::srand(seed);

    for (int i = 0; i < rolls; i++) {
        int outcome = std::rand() % sides;
        local_result[outcome]++;
    }

    for (int i = 0; i < sides; i++) result[i] += local_result[i];
}

int main(int argc, char** argv) {
    const int rolls = argv[1] ? std::atoi(argv[1]) : 10000;
    const int num_threads = std::thread::hardware_concurrency();  // Use available cores

    sides_array results;
    for (auto& r : results) r = 0;

    std::vector<std::thread> threads;
    int rolls_per_thread = rolls / num_threads;

    for (int i = 0; i < num_threads; i++) {
        unsigned int seed = static_cast<unsigned int>(std::time(nullptr)) + i;
        threads.emplace_back(simulate_dice_rolls, rolls_per_thread, std::ref(results), seed);
    }

    for (auto& thread : threads) thread.join();

    for (int i = 0; i < sides; i++)
        std::cout << i + 1 << ": " << (float)results[i] / (float)rolls << std::endl;
}
