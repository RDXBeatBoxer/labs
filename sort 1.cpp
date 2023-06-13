#include <iostream>
#include <algorithm>
#include<chrono>

using namespace std;
using namespace std::chrono;

void merge(int*, int, int, int);
void newBucket(int**, int);

void countSort(int* A, int SIZE, int range)
{
    int* sorted = new int[SIZE];
    int* count = new int[range + 1] {};

    for (int i = 0; i < SIZE; i++)
        ++count[A[i]];

    for (int i = 1; i <= range; ++i)
        count[i] += count[i - 1];

    for (int i = sizeof(*A) - 1; i >= 0; --i)
    {
        sorted[count[A[i]] - 1] = A[i];
        --count[A[i]];
    }

    for (int i = 0; i < SIZE; ++i)
        A[i] = sorted[i];

    delete[] sorted;
    delete[] count;
}

void merge_sort(int* arr, int low, int high)
{
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}

void merge(int* arr, int low, int high, int mid)
{
    int i, j, k;
    int* c = new int[high];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
    }
}

void bucketSort(int* arr, int n)
{
    int** b = new int* [n];
    for (int i = 0; i < n; i++)
        b[i] = new int[9];
    int ost, temp;

    for (int i = 1; i <= 100; i *= 10)
    {
        newBucket(b, n);
        int count = 0;
        for (int a = 0; a < n; a++)
        {
            temp = arr[a] / i;
            ost = temp % 10;
            b[ost][i] = arr[a];
        }
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < n; y++)
            {
                if (b[x][y] != -1)
                {
                    arr[count] = b[x][y];
                    ++count;
                }
            }
        }
    }


    delete[] b;
}

void newBucket(int** b, int size)
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < size; j++)
            b[i][j] = -1;
}

void quickSort(int* arr, int start, int size)
{
    int left = start, right = size;
    int mid = arr[(left + right) / 2];

    while (left <= right)
    {
        while (arr[left] < mid)
            ++left;
        while (arr[right] > mid)
            --right;
        if (left <= right)
        {
            int buf = arr[left];
            arr[left] = arr[right];
            arr[right] = buf;
            left++;
            right--;
        }
    }
    if (start < right)
        quickSort(arr, start, right);
    if (size > left)
        quickSort(arr, left, size);

}

void randArr(int* arr, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
        arr[i] = 0 + rand() % 9;
}

int main()
{
    srand(time(NULL));


    int SIZE, range = 10;
    cout << "Enter size of array: ";
    cin >> SIZE;

    int* arr = new int[SIZE];

    randArr(arr, SIZE);
    auto start = high_resolution_clock::now();
    countSort(arr, SIZE, range);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Count Sort: " << duration.count() << " micsec\n";

    randArr(arr, SIZE);
    auto startM = high_resolution_clock::now();
    merge_sort(arr, 0, SIZE - 1);
    auto endM = high_resolution_clock::now();
    auto durationM = duration_cast<microseconds>(endM - startM);
    cout << "Merge Sort: " << durationM.count() << " micsec\n";

    randArr(arr, SIZE);
    auto startB = high_resolution_clock::now();
    bucketSort(arr, SIZE);
    auto endB = high_resolution_clock::now();
    auto durationB = duration_cast<microseconds>(endB - startB);
    cout << "Bucket Sort: " << durationB.count() << " micsec\n";

    randArr(arr, SIZE);
    auto startQs = high_resolution_clock::now();
    quickSort(arr, 0, SIZE - 1);
    auto endQs = high_resolution_clock::now();
    auto durationQs = duration_cast<microseconds>(endQs - startQs);
    cout << "Quick Sort: " << durationQs.count() << "micsec\n";


    delete[] arr;

    return 0;
}