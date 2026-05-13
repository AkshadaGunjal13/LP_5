#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n; i++)
    {
        // Odd phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Even phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Display Array
void display(vector<int>& arr)
{
    for(int x : arr)
        cout << x << " ";

    cout << endl;
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> seqArr = arr;
    vector<int> parArr = arr;

    // Sequential Bubble Sort
    auto start1 = high_resolution_clock::now();
    sequentialBubbleSort(seqArr);
    auto end1 = high_resolution_clock::now();

    // Parallel Bubble Sort
    auto start2 = high_resolution_clock::now();
    parallelBubbleSort(parArr);
    auto end2 = high_resolution_clock::now();

    // Output
    cout << "\nSequential Bubble Sort:\n";
    display(seqArr);

    cout << "\nParallel Bubble Sort:\n";
    display(parArr);

    // Time
    auto time1 = duration_cast<microseconds>(end1 - start1);
    auto time2 = duration_cast<microseconds>(end2 - start2);

    cout << "\nSequential Time: "
         << time1.count() << " microseconds";

    cout << "\nParallel Time: "
         << time2.count() << " microseconds";

    return 0;
}




Parallel Bubble Sort using OpenMP
Algorithm
Read array elements.
Perform Odd-Even Bubble Sort:
Compare odd indexed pairs in parallel.
Compare even indexed pairs in parallel.
Swap elements if they are in wrong order.
Repeat for all passes until array gets sorted.
Display sorted array and execution time.
Time Complexity
Sequential Bubble Sort

O(n2)

Parallel Bubble Sort

O(n2/p)

n = Number of elements
p = Number of processors/threads
Space Complexity

O(1)

4. Parallel Merge Sort using OpenMP
Algorithm
Divide the array into two halves.
Recursively divide each half until single elements remain.
Sort subarrays in parallel using OpenMP sections/tasks.
Merge sorted subarrays.
Repeat merging until complete array is sorted.
Time Complexity
Sequential Merge Sort

O(nlogn)

Parallel Merge Sort

O(nlogn)

n = Number of elements
p = Number of processors/threads
Space Complexity

O(n)