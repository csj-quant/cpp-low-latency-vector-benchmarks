# ✅ **vector_memory_layout.md**

```
# Vector Memory Layout (mini_vector<int>)

This document summarizes the observed memory behavior of `mini_vector<int>` during
push_back operations. The goal is to understand how size, capacity, and memory
addresses evolve as the vector grows.

---

## 1. Size–Capacity Relationship (First 20 Pushes)

i    size   capacity
---------------------
0    1      1
1    2      2
2    3      4
3    4      4
4    5      8
5    6      8
6    7      8
7    8      8
8    9      16
9    10     16
10   11     16
11   12     16
12   13     16
13   14     16
14   15     16
15   16     16
16   17     32
17   18     32
18   19     32

### Interpretation

- Capacity grows as `1 → 2 → 4 → 8 → 16 → 32 ...`
- Between these power-of-two jumps, the capacity stays constant.
- Size increases by 1 each push, but capacity only grows when size exceeds the current capacity.
- This demonstrates exponential growth (doubling), the key technique that enables amortized `O(1)` push_back.

---

## 2. Memory Reallocation Log

```

size=1  capacity=1    data=0x55e7beb816c0
size=2  capacity=2    data=0x55e7beb816e0
size=3  capacity=4    data=0x55e7beb816c0
size=5  capacity=8    data=0x55e7beb81700
size=9  capacity=16   data=0x55e7beb81730
size=17 capacity=32   data=0x55e7beb81780
size=33 capacity=64   data=0x55e7beb81810
size=65 capacity=128  data=0x55e7beb81920
size=129 capacity=256 data=0x55e7beb81b30
size=257 capacity=512 data=0x55e7beb81f40

```

### Key Observations

1. **Reallocation happens only when crossing powers of two**  
   Sizes triggering reallocations:  
   `1, 2, 3, 5, 9, 17, 33, 65, 129, 257`

2. **Each reallocation changes the base address**  
   This means:
   - Data is fully moved to a new block.
   - All pointers and iterators become invalid.

3. **Memory growth curve is perfectly geometric**  
   This matches real `std::vector` behavior in most standard libraries.

---

## Summary

The memory layout confirms:
- Contiguous storage
- Exponential growth
- Full reallocation on expansion
- Strong alignment with `std::vector` internals

Understanding this behavior is essential for low-latency system design, where avoiding reallocations with `reserve()` is often mandatory.
