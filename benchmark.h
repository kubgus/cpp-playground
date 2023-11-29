#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#define BM_NOW std::chrono::system_clock::now()

template <typename _Func>
class Benchmark
{
public:
    Benchmark(const _Func &func);

    template <typename... _Args>
    void Run(_Args... args);
    void Print(const char *debugName);

    inline std::vector<double> Get();

private:
    const _Func &m_Func;
    std::vector<double> m_Results;
};