# Vector Memory Layout (mini_vector<int>)

This document summarizes how size, capacity, and memory addresses evolve in `mini_vector<int>` during push_back operations. The data confirms exponential growth and full reallocations.

## Size–Capacity Progression (first 20 pushes)

## i    size   capacity

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

Interpretation:

* Capacity doubles: 1 → 2 → 4 → 8 → 16 → 32 → …
* Between doublings, capacity stays constant.
* push_back only triggers reallocation when size exceeds current capacity.

## Reallocation Log (address changes)

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

Observations:

* Reallocations occur when size crosses powers of two.
  Trigger points: 1, 2, 3, 5, 9, 17, 33, 65, 129, 257
* Each reallocation moves data to a new address.
* Confirms: vector uses contiguous memory + exponential growth.

## Summary

mini_vector demonstrates classic vector behavior:

* geometric capacity growth
* full reallocation when expanding
* contiguous memory layout
* predictable push_back cost (amortized O(1))

---
