# Vector Memory Layout (mini_vector<int>)

This document summarizes how size, capacity, and memory addresses evolve in `mini_vector<int>` during push_back operations. The data confirms exponential growth and full reallocations.

## Size–Capacity Progression (first 20 pushes)

## i    size   capacity

0    1      1 <br> 
1    2      2 <br>
2    3      4 <br>
3    4      4 <br>
4    5      8 <br>
5    6      8 <br>
6    7      8 <br>
7    8      8 <br>
8    9      16 <br>
9    10     16 <br>
10   11     16 <br>
11   12     16 <br>
12   13     16 <br>
13   14     16 <br>
14   15     16 <br>
15   16     16 <br>
16   17     32 <br>
17   18     32 <br>
18   19     32 <br>

Interpretation:

* Capacity doubles: 1 → 2 → 4 → 8 → 16 → 32 → …
* Between doublings, capacity stays constant.
* push_back only triggers reallocation when size exceeds current capacity.

## Reallocation Log (address changes)

size=1  capacity=1    data=0x55e7beb816c0 <br>
size=2  capacity=2    data=0x55e7beb816e0 <br>
size=3  capacity=4    data=0x55e7beb816c0 <br>
size=5  capacity=8    data=0x55e7beb81700 <br>
size=9  capacity=16   data=0x55e7beb81730 <br>
size=17 capacity=32   data=0x55e7beb81780 <br>
size=33 capacity=64   data=0x55e7beb81810 <br>
size=65 capacity=128  data=0x55e7beb81920 <br>
size=129 capacity=256 data=0x55e7beb81b30 <br>
size=257 capacity=512 data=0x55e7beb81f40 <br> 

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

