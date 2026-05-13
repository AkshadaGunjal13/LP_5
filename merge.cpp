#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Merge Function
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right, int depth)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        if(depth <= 4)
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

// Display Function
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

    // Sequential Merge Sort
    auto start1 = high_resolution_clock::now();
    sequentialMergeSort(seqArr, 0, n - 1);
    auto end1 = high_resolution_clock::now();

    // Parallel Merge Sort
    auto start2 = high_resolution_clock::now();
    parallelMergeSort(parArr, 0, n - 1, 0);
    auto end2 = high_resolution_clock::now();

    // Output
    cout << "\nSequential Merge Sort:\n";
    display(seqArr);

    cout << "\nParallel Merge Sort:\n";
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