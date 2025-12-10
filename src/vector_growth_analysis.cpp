#include <iostream>
#include "mini_vector.hpp"

int main()
{
    mini_vector<int> v;
    std::cout << "i\tsize\tcapacity\n";
    std::cout << "-------------------\n";

    for (int i = 0; i < 64; i++)
    {
        v.push_back(i);
        std::cout << i << "\t" << v.size() << "\t" << v.capacity() << "\n";
    }
    return 0;
}