#include <algorithm>
#include <iostream>
using namespace std;


int InterpolSearch(int A[], int key, int N)
{
	int mid, left = 0, right = N - 1;
	if (N != 1)
	{
		while (A[left] <= key && A[right] >= key)
		{
			mid = left + ((key - A[left]) * (right - left)) / (A[right] - A[left]);
			if (A[mid] < key)
				left = mid + 1;
			else
				if (A[mid] > key)
					right = mid - 1;
				else
					return mid;
		}
	}
	else
		A[left] = A[0];
	if (A[left] == key)
		return left;
	else
		return -1;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int N, key, a;
	cout << "Enter the number of elements in the array: ";
	cin >> N;
	if (N < 1)
	{
		cout << "The array does not exist!\n";
		return 0;
	}
	int* mas = new int[N];
	cout << "enter " << N << " ordered array elements : ";
	for (int i = 0; i < N; i++)
		cin >> mas[i];
	sort(mas, mas + N); 
	cout << "Source array: ";
	for (int i = 0; i < N; i++)
		cout << mas[i] << " ";
	cout << "\nEnter the item you want to search for: ";
	cin >> key;
	a = InterpolSearch(mas, key, N);
	if (a == -1)
		cout << "Item Not Found\n";
	else
		cout << "Item Number: " << a + 1 << endl;
}