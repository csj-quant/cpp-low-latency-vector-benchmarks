# cpp-low-latency-vector-benchmarks

High-resolution benchmarks and diagnostics for understanding `std::vector` internals, memory layout, growth behavior, iterator invalidation, and low-latency performance impact.
This project is part of a broader study on writing predictable, high-performance C++ systems for quant and HFT workloads.

---

## 📌 Purpose

This repository analyzes `std::vector` from a systems and performance perspective:

* how memory is allocated and reorganized
* how capacity grows
* how many reallocations occur and when
* how pointer stability and iterator invalidation behave
* how to avoid latency spikes caused by unexpected growth
* how manual reservation improves throughput

It also provides a minimal reimplementation of `std::vector` to expose internal mechanisms clearly.

---

## 🧩 Repository Structure

```
cpp-low-latency-vector-benchmarks/
│
├── src/
│   ├── mini_vector.hpp
│   ├── mini_vector.cpp
│   ├── vector_reallocation_diagnostics.cpp
│   ├── vector_growth_analysis.cpp
│   ├── vector_reserve_vs_noreserve.cpp
│
└── docs/
    ├── vector_memory_layout.md
    ├── vector_invalidation_table.md
    ├── vector_growth_behavior.md
```

---

## 🚀 Implemented Components

### 1. `mini_vector<T>`

A minimal implementation of a dynamic array exposing the fundamentals of:

* raw allocation using `operator new[]`
* element construction via placement-new
* destruction using explicit destructor calls
* manual capacity management
* reallocation on push-back

This component mirrors how `std::vector` operates internally, allowing precise observation of:

* pointer changes
* capacity doubling
* move vs copy behavior
* growth sequences

---

### 2. Reallocation Diagnostics

`vector_reallocation_diagnostics.cpp` prints the address of `data_` during early growth:

```
size=1  capacity=1    data=0x...
size=2  capacity=2    data=0x...
size=3  capacity=4    data=0x...
size=5  capacity=8    data=0x...
...
```

This confirms that:

* capacity follows a doubling strategy
* every growth event produces a **new memory block**
* all existing elements are moved during the event

---

### 3. Growth Pattern Analysis

`vector_growth_analysis.cpp` logs size–capacity pairs:

```
0 → 1  
1 → 1  
2 → 2  
3 → 4  
4 → 4  
5 → 8  
...
```

The measurements confirm exponential growth:

```
1 → 2 → 4 → 8 → 16 → 32 → …
```

This matches the behavior of libstdc++ and libc++.

---

### 4. Reserve vs No Reserve Benchmark

`vector_reserve_vs_noreserve.cpp` compares runtime for 1,000,000 pushes:

| Case            | Final Capacity | Time (seconds) |
| --------------- | -------------- | -------------- |
| Without reserve | 1,048,576      | 0.0064167      |
| With reserve    | 1,000,000      | 0.00449794     |

Key takeaways:

* Reserving capacity avoids all intermediate reallocations
* Performance improved by nearly **30%** in this experiment
* Latency stability improves significantly
* This reinforces why HFT code always pre-allocates

---

## 📄 Documentation (docs/)

### **vector_memory_layout.md**

Explains the internal structure:

* `begin()` pointer
* size
* capacity
* contiguous memory guarantees
* pointer arithmetic

### **vector_invalidation_table.md**

Describes exactly which operations invalidate:

* pointers
* references
* iterators

### **vector_growth_behavior.md**

Summarizes actual measured growth behavior:

* full size–capacity table
* reallocation log
* interpretation of doubling strategy
* analysis of reserve vs non-reserve behavior

---

## 🧪 Key Insights

* `std::vector` reallocates only on boundary crossings (power-of-two points).
* Reallocation moves all elements and invalidates all iterators.
* Doubling growth ensures amortized O(1) push_back.
* Pre-reserving memory eliminates unpredictable spikes in latency.
* Contiguous storage yields superior cache locality, crucial for low-latency systems.

---

## 🔧 Build Instructions

```
mkdir -p build
cd build
cmake ..
make -j8
```

Executables:

* `vector_reallocation_diagnostics`
* `vector_growth_analysis`
* `vector_reserve_vs_noreserve`

---

## 📦 Future Additions

This repository will expand to include:

* improved mini_vector with move-only types
* allocator benchmarking
* small-buffer optimization (SBO/SSO) analysis
* contiguous vs non-contiguous container comparisons
* cache-line–aware profiling
