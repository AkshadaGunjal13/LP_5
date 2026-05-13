#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ---------------- SEQUENTIAL BUBBLE SORT ----------------
void sequentialBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- PARALLEL BUBBLE SORT ----------------
void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- MERGE FUNCTION ----------------
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// ---------------- SEQUENTIAL MERGE SORT ----------------
void sequentialMergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------
void parallelMergeSort(vector<int>& arr, int left, int right, int depth)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        if (depth <= 4)
        {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);

                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        }
        else
        {
            sequentialMergeSort(arr, left, mid);
            sequentialMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

// ---------------- DISPLAY FUNCTION ----------------
void display(vector<int>& arr)
{
    for (int x : arr)
        cout << x << " ";

    cout << endl;
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> bubbleSeq = arr;
    vector<int> bubblePar = arr;
    vector<int> mergeSeq = arr;
    vector<int> mergePar = arr;

    // Sequential Bubble Sort
    auto start1 = high_resolution_clock::now();
    sequentialBubbleSort(bubbleSeq);
    auto end1 = high_resolution_clock::now();

    // Parallel Bubble Sort
    auto start2 = high_resolution_clock::now();
    parallelBubbleSort(bubblePar);
    auto end2 = high_resolution_clock::now();

    // Sequential Merge Sort
    auto start3 = high_resolution_clock::now();
    sequentialMergeSort(mergeSeq, 0, n - 1);
    auto end3 = high_resolution_clock::now();

    // Parallel Merge Sort
    auto start4 = high_resolution_clock::now();
    parallelMergeSort(mergePar, 0, n - 1, 0);
    auto end4 = high_resolution_clock::now();

    // Output
    cout << "\nSequential Bubble Sort Result:\n";
    display(bubbleSeq);

    cout << "\nParallel Bubble Sort Result:\n";
    display(bubblePar);

    cout << "\nSequential Merge Sort Result:\n";
    display(mergeSeq);

    cout << "\nParallel Merge Sort Result:\n";
    display(mergePar);

    // Time calculation
    auto time1 = duration_cast<microseconds>(end1 - start1);
    auto time2 = duration_cast<microseconds>(end2 - start2);
    auto time3 = duration_cast<microseconds>(end3 - start3);
    auto time4 = duration_cast<microseconds>(end4 - start4);

    cout << "\nPerformance Comparison:\n";

    cout << "\nSequential Bubble Sort Time: "
         << time1.count() << " microseconds";

    cout << "\nParallel Bubble Sort Time: "
         << time2.count() << " microseconds";

    cout << "\nSequential Merge Sort Time: "
         << time3.count() << " microseconds";

    cout << "\nParallel Merge Sort Time: "
         << time4.count() << " microseconds";

    return 0;
}


Sequential Bubble Sort Result:
11 12 22 25 34 64

Parallel Bubble Sort Result:
11 12 22 25 34 64

Sequential Merge Sort Result:
11 12 22 25 34 64

Parallel Merge Sort Result:
11 12 22 25 34 64