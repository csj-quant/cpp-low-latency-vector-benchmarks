# cpp-low-latency-vector-benchmarks

This repository explores the internals of `std::vector` from a low-latency, systems-programming, and quant-developer perspective. It includes a hand-written minimal vector implementation, diagnostics for reallocation behavior, and benchmarks comparing different growth strategies. The goal is to understand how vectors manage memory, how capacity grows, how reallocations impact performance, and why vectors dominate high-performance C++ codebases.

---

## Project Structure

src/
• mini_vector.hpp
• mini_vector.cpp
• vector_reallocation_diagnostics.cpp
• vector_growth_analysis.cpp
• vector_reserve_vs_noreserve.cpp

---

## 1. mini_vector<T>

A small self-written vector class demonstrating how `std::vector` works internally.
Features implemented:

• Manual raw allocation using operator new[].
• Placement-new construction of elements.
• Manual destruction of objects.
• push_back(const T&) with automatic growth.
• reserve(size_t) to grow capacity ahead of time.
• operator[] for indexed access.
• Full ownership of a contiguous buffer, similar to libstdc++.

This implementation makes it clear how vectors store `data`, `size`, and `capacity`, and why reallocation invalidates pointers and iterators.

---

## 2. Reallocation Diagnostics

The program prints the vector’s size, capacity, and the address of the underlying buffer after each push_back, revealing exactly when reallocations occur.

Example of your actual output:

size=1 capacity=1 data=0x…
size=2 capacity=2 data=0x…
size=3 capacity=4 data=0x…
size=5 capacity=8 data=0x…
size=9 capacity=16 data=0x…
…
size=257 capacity=512 data=0x…

This confirms exponential growth (1 → 2 → 4 → 8 → …) and amortized O(1) push_back.

---

## 3. Vector Growth Analysis

Logs the capacity for every size from 0 to 64. Your results show:

• capacity doubled at sizes 1, 2, 4, 8, 16, 32, 64
• in-between pushes reused existing capacity
• no unnecessary allocations

This fully matches the expected growth pattern of libstdc++.

---

## 4. Benchmark: reserve vs no reserve

Two tests were run for inserting 1,000,000 integers.

Without reserve():
• size: 1,000,000
• capacity: 1,048,576
• reallocations: many
• time: 0.0064167 seconds

With reserve(1’000’000):
• size: 1,000,000
• capacity: 1,000,000
• reallocations: zero
• time: 0.00449794 seconds

Reserve is significantly faster because:
• no reallocation spikes
• no copying/moving of elements
• consistent memory address
• better cache behavior
• zero allocator calls during growth

This is why performance-sensitive systems must preallocate.

---

## 5. Why This Matters (Quant & HFT Perspective)

Understanding vector internals is crucial for:
• predictable latency under heavy throughput
• eliminating hidden allocations
• optimizing cache locality
• writing high-performance order-book and market-data pipelines
• system-design performance interviews (HRT, Citadel, Jane Street, IMC)

This repository forms the foundation for later topics like custom allocators, ring buffers, arena memory, and lock-free development.

---

## 6. How to Build and Run

From build directory:

cmake ..
make

Executables:
• vector_reallocation_diagnostics
• vector_growth_analysis
• vector_reserve_vs_noreserve
