#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
const int arraySize = 10;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int arr[arraySize];

    for (int i = 0; i < arraySize; i++) {
        arr[i] = rand() % 100; 
    }

    cout << "Original array: ";
    printArray(arr, arraySize);

    int k = 3;  
    if (k >= 0 && k < arraySize) {
        for (int i = k; i < arraySize - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arraySize--;
    }

    for (int i = arraySize - 1; i >= 0; i--) {
        if (arr[i] % 2 == 0) {
            for (int j = arraySize; j > i + 1; j--) {
                arr[j] = arr[j - 1];
            }
            arr[i + 1] = 0;
            arraySize++;
        }
    }

    cout << "Modified array: ";
    printArray(arr, arraySize);

    return 0;
}
