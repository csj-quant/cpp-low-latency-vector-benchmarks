# Vector Growth Behavior

This document summarizes how `std::vector` grows in practice, based on empirical measurements and reallocation logs collected from custom diagnostics. Understanding this behavior is crucial for writing low-latency C++ code and minimizing unnecessary reallocations.

## Growth Pattern (Measured)

Observed size–capacity evolution for the first pushes:

size → 0, capacity → 1
size → 1, capacity → 1
size → 2, capacity → 2
size → 3, capacity → 4
size → 4, capacity → 4
size → 5, capacity → 8
size → 6–8, capacity → 8
size → 9, capacity → 16
size → 10–15, capacity → 16
size → 16, capacity → 16
size → 17, capacity → 32
… and so on.

This confirms the typical exponential growth strategy: when capacity is exceeded, it approximately **doubles**.

## Reallocation Diagnostics (Actual Address Logs)

A reallocation happens only when size crosses a power-of-two boundary:

* size = 1 → capacity = 1 → new address
* size = 2 → capacity = 2 → new address
* size = 3 → capacity = 4 → new address
* size = 5 → capacity = 8 → new address
* size = 9 → capacity = 16 → new address
* size = 17 → capacity = 32 → new address
* size = 33 → capacity = 64 → new address
* size = 65 → capacity = 128 → new address
* size = 129 → capacity = 256 → new address
* size = 257 → capacity = 512 → new address

Between these points, the internal pointer remains stable.

Key observations:

1. **Capacity grows exponentially** (x2 each time).
2. **Address changes only at growth events**, proving a real reallocation.
3. All elements are moved to the new block whenever capacity increases.

This matches both libstdc++ and libc++ growth behavior (typically 2× expansion).

## Reserve vs No Reserve (Performance Impact)

Benchmark results for pushing **1,000,000 integers**:

Without `reserve()`

* size = 1,000,000
* capacity = 1,048,576
* time ≈ 0.0064167 seconds

With `reserve(1'000'000)`

* size = 1,000,000
* capacity = 1,000,000
* time ≈ 0.00449794 seconds

**Result: ~30% faster with reserve()**

Reasons:

* No intermediate reallocations
* No repeated copying/moving of elements
* Fewer allocator calls
* Improved cache predictability

## Summary

* `std::vector` grows exponentially (≈2× rule).
* Reallocations occur exactly when size exceeds current capacity.
* Reallocation moves all elements and changes the internal buffer address.
* Using `reserve()` significantly improves performance for known sizes.
* Avoiding reallocations is essential in low-latency systems.
