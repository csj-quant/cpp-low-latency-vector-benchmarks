/*
You are given an array of 200 million floating-point numbers (prices).
You must compute a moving average with window = 64:
MA[i] = (A[i] + A[i-1] + ... + A[i-63]) / 64
Constraints:
Do it in under a few milliseconds
NO dynamic allocations inside the loop
NO linked lists, NO queues → too slow
NO virtual calls
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

// nanosecond diff
inline long long ns_diff(const timespec &a, const timespec &b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000 + (b.tv_nsec - a.tv_nsec);
}

int main()
{
    const int W = 64;
    const int N = 200000000;

    std::vector<float> a(N);
    std::vector<float> out(N);

    // fill data at random
    for (int i = 0; i < N; i++)
    {
        a[i] = (float)(rand() % 1000);
    }

    float sum = 0.0f;
    //warm up - calc for the first window of 64 nums
    for (int i = 0; i < W; i++)
    {
        sum += a[i];
    }
    out[W-1] = sum/W;

    timespec t1{}, t2{};
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

    // sliding window
    for (int i = W; i < N; i++)
    {
        sum += a[i]; // add the new element in right
        sum -= a[i-W]; // remove the first element of the prev window
        out[i] = sum/W; // recalculate mov avg for that window and store in out[i]
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    long long ns = ns_diff(t1,t2);

    // ---- CRITICAL PART: checksum prevents optimization ----
    double checksum = 0.0;
    for (int i = N - 100; i < N; i++)
        checksum += out[i];
    std::cout << "Checksum = " << checksum << "\n";
    // --------------------------------------------------------

    std::cout << "Processed " << N << " samples\n";
    std::cout << "Window = " << W << "\n";
    std::cout << "Time = " << ns/1e6 << " ms \n";
    std::cout << "Throughput = " << (double)N / (ns/1e9)/1e6 << " million ops/sec\n";
    return 0;

/*
Checksum = 45540.8
Processed 200000000 samples
Window = 64
Time = 430.185 ms
Throughput = 464.916 million ops/sec
The loop does 2 reads and 1 write per iteration
Total ~12 bytes read/written per iteration
Over 200 million iterations: ~2.4 GB of memory traffic
At 430 ms, bandwidth used =
2.4 GB / 0.43 ≈ 5.5 GB/s

Typical laptop RAM gives 6–20 GB/s throughput, so this is perfectly valid.
*/
}