#include <iostream>
#include "mini_vector.hpp"

int main()
{
    mini_vector<int> v;
    std::cout << "Reallocation Diagnostics for mini_vector<int> \n";
    std::cout << "------------------------------------------------\n";

    void* last_address = nullptr;

    for (int i = 0; i < 500; i++)
    {
        v.push_back(i);

        // address of the underlying array
        void* current = static_cast<void*>(v.data());

        if (current != last_address)
        {
            std::cout << "size=" << v.size() << " capacity=" << v.capacity() << " data="<< current <<"\n";
            last_address = current;
        }
    }

    return 0;
}