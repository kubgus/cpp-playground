#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#define BM_NOW std::chrono::system_clock::now()

template <typename _Func>
class Benchmark
{
public:
    Benchmark(const _Func &func) : m_Func(func) {}

    template <typename... _Args>
    void Run(_Args... args)
    {
        auto start = BM_NOW;
        m_Func(args...);
        auto end = BM_NOW;
        m_Results.push_back((end - start).count() / 1000000.0);
    }
    void Print(const char *debugName)
    {
        std::cout << "==== Results for " << debugName << " ====" << std::endl;
        for (int i = 0; i < m_Results.size(); i++)
            std::cout << i + 1 << ": " << m_Results[i] << "ms" << std::endl;
    }

    inline std::vector<double> Get() { return m_Results; }

private:
    const _Func &m_Func;
    std::vector<double> m_Results;
};

int main()
{
}