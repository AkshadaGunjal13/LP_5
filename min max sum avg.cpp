#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

    int minimum = INT_MAX;
    int maximum = INT_MIN;
    long long sum = 0;
    double average;

    // Start Time
    auto start = high_resolution_clock::now();

    // Parallel Reduction
    #pragma omp parallel for reduction(min:minimum) reduction(max:maximum) reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < minimum)
        {
            minimum = arr[i];
        }

        if(arr[i] > maximum)
        {
            maximum = arr[i];
        }

        sum += arr[i];
    }

    average = (double)sum / n;

    // End Time
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    // Output
    cout << "\nResults:\n";

    cout << "Minimum Element = " << minimum << endl;
    cout << "Maximum Element = " << maximum << endl;
    cout << "Sum = " << sum << endl;
    cout << "Average = " << average << endl;

    cout << "\nExecution Time = "
         << duration.count()
         << " microseconds" << endl;

    return 0;
}



Definition
Parallel Reduction is used to combine multiple values into a single result using parallel threads.
OpenMP reduction improves performance by dividing work among threads.
2. OpenMP Reduction Syntax
#pragma omp parallel for reduction(operator:variable)

Example:

#pragma omp parallel for reduction(+:sum)
3. Reduction Operators
Operation	Operator
Sum	+
Multiplication	*
Minimum	min
Maximum	max
4. Important Variables Initialization
Variable	Initialization
Minimum	INT_MAX
Maximum	INT_MIN
Sum	0
5. Formula for Average

Average=Sum/n
	​


6. Time Complexities
Sequential Complexity

O(n)

Parallel Complexity

O(​n/p)

Where:

n = number of elements
p = number of processors/threads
7. Space Complexity

O(1)

