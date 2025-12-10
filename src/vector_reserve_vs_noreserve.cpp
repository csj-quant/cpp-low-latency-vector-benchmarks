#include <iostream>
#include <chrono>
#include "mini_vector.hpp"

using Clock = std::chrono::high_resolution_clock;

int main()
{
    constexpr int N = 1000000;

    // without reserve
    {
        mini_vector<int> v;
        auto start = Clock::now();
        for (int i = 0; i < N; ++i)
        {
            v.push_back(i);
        }
        auto end = Clock::now();
        std::chrono::duration<double> sec = end - start;

        std::cout << "Without reserve:\n";
        std::cout << " size = " << v.size() << "\n";
        std::cout << " capacity = " << v.capacity() << "\n";
        std::cout << " time = " << sec.count() << "\n\n";
    }

    // with reserve
    {
        mini_vector<int> v;
        v.reserve(N);
        auto start = Clock::now();
        for (int i = 0; i < N; ++i)
        {
            v.push_back(i);
        }
        auto end = Clock::now();
        std::chrono::duration<double> sec = end - start;

        std::cout << "With reserve:\n";
        std::cout << " size = " << v.size() << "\n";
        std::cout << " capacity = " << v.capacity() << "\n";
        std::cout << " time = " << sec.count() << "\n\n";
    }

    return 0;
}