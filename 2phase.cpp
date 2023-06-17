#include <iostream>
using namespace std;

void twoPhaseSort(int* arr, int size)
{
for (int i = 0; i < size - 1; i++)
{
for (int j = 0; j < size - i - 1; j++)
{
if (arr[j] > arr[j + 1]) {
int temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
}
}
}
for (int i = 0; i < size / 2; i++)
{
int temp = arr[i];
arr[i] = arr[size - i - 1];
arr[size - i - 1] = temp;
}
for (int i = 0; i < size; i++)
{
cout « arr[i] « " ";
}
cout « endl;
}

void main()
{
int* arr = new int[8];
for (int i = 0; i < 8; i++)
{
cin » arr[i];
}

twoPhaseSort(arr, 8);

delete[] arr;
}