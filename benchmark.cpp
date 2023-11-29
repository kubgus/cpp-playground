#include "benchmark.h"

template <typename _Func>
inline Benchmark<_Func>::Benchmark(const _Func &func)
    : m_Func(func) {}

template <typename _Func>
template <typename... _Args>
inline void Benchmark<_Func>::Run(_Args... args)
{
    auto start = BM_NOW;
    m_Func(args...);
    auto end = BM_NOW;
    m_Results.push_back((end - start).count() / 1000000.0);
}

template <typename _Func>
void Benchmark<_Func>::Print(const char *debugName)
{
    std::cout << "==== Results for " << debugName << " ====" << std::endl;
    for (int i = 0; i < m_Results.size(); i++)
        std::cout << i + 1 << ": " << m_Results[i] << "ms" << std::endl;
}

template <typename _Func>
inline std::vector<double> Benchmark<_Func>::Get()
{
    return m_Results;
}