#include <iostream>
#include<chrono>

using namespace std;
using namespace std::chrono;

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

void Shell(int A[], int n)
{
	int d = n;
	d /= 2;
	int j;

	while (d > 0)
	{
		for (int i = 0; i < n - d; i++)
		{
			j = i;
			while (j >= 0 && A[j] > A[j + d])
			{
				int count = A[j];
				A[j] = A[j + d];
				A[j + d] = count;
				j--;
			}
		}
		d = d / 2;
	}
}

void randArr(int* arr, int SIZE)
{
	for (int i = 0; i < SIZE; i++)
		arr[i] = 0 + rand() % 9;
}

void printArr(int arr[], int SIZE)
{
	for (int i = 0; i < SIZE; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int size;

	srand(time(NULL));

	cout << "size of array > ";
	cin >> size;

	int* A = new int[size];

	randArr(A, size);
	cout << "sort of Hoare: \n";
	cout << "unsorted array: ";
	printArr(A, size);
	auto startQs = high_resolution_clock::now();
	quickSort(A, 0, size - 1);
	auto endQs = high_resolution_clock::now();
	auto durationQs = duration_cast<microseconds>(endQs - startQs);
	cout << "sorted array: ";
	printArr(A, size);
	cout << "Quick Sort: " << durationQs.count() << " micsec\n";

	cout << "\n";

	randArr(A, size);
	cout << "sort of shell: \n";
	cout << "unsorted array: ";
	printArr(A, size);
	auto start = high_resolution_clock::now();
	Shell(A, size);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "sorted array: ";
	printArr(A, size);
	cout << "Shell Sort: " << duration.count() << " micsec\n";

	delete[] A;

	return 0;
}