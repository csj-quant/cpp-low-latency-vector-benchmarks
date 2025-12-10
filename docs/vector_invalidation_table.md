# Vector Iterator and Pointer Invalidation Table

This document summarizes when iterators, references, and pointers into a vector become invalid after modifications. Understanding these rules is essential for writing correct and efficient C++ code.

## Invalidation Rules by Operation

Operation: push_back (no reallocation)
Iterators invalidated: only end()
Reason: Data buffer unchanged; only the last position shifts.

Operation: push_back (with reallocation)
Iterators invalidated: all
Reason: New memory block allocated; all elements moved.

Operation: insert at end (no reallocation)
Iterators invalidated: end()
Reason: Final position changes.

Operation: insert in middle (no reallocation)
Iterators invalidated: all iterators at or after insertion point
Reason: Elements are shifted to the right.

Operation: insert (with reallocation)
Iterators invalidated: all
Reason: Full reallocation occurs before insertion.

Operation: erase (non-end element)
Iterators invalidated: all iterators at or after erased position
Reason: Elements shift left to fill the gap.

Operation: erase at end
Iterators invalidated: end()
Reason: Size changes, but underlying storage remains unchanged.

Operation: reserve(new_capacity > old_capacity)
Iterators invalidated: all
Reason: Reallocation always occurs when capacity expands.

Operation: resize (shrink)
Iterators invalidated: iterators to removed elements
Reason: Destruction of excess elements.

Operation: resize (grow, no reallocation)
Iterators invalidated: end()
Reason: New elements appended; buffer unchanged.

Operation: resize (grow, reallocation)
Iterators invalidated: all
Reason: New memory allocation for expanded storage.

Operation: clear()
Iterators invalidated: all except begin()
Reason: All elements destroyed; begin() remains valid but equal to end().

Operation: swap(a, b)
Iterators invalidated: all iterators for both vectors
Reason: Buffers exchanged; old addresses no longer point to original data.

## Summary

* Any operation that causes **reallocation** invalidates every iterator and pointer.
* Operations that **shift elements** invalidate iterators after the affected point.
* push_back is safe only when capacity is already large enough.
* erase and insert have well-defined but non-trivial invalidation behavior.

These rules match real-world std::vector guarantees and are critical for designing safe iterator-based algorithms.
