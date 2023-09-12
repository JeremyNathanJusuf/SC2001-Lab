#include <iostream>
using namespace std;

void swap(int* left, int* right) {
    int temp = *right;
    *right = *left;
    *left = temp;
}

void insertionSort(int* array, int size) {
    for (int i=1; i<size; i++) {
        for (int j=i; j>0; j--) {
            if (array[j-1] > array[j]) {
                swap(&array[j-1], &array[j]);
            }
            else break;
        }
    }
}

int main() {
    int ar[] = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};

    for (int i : ar)
        cout << i << " ";
    cout << endl;

    insertionSort(ar, 12);

    for (int i : ar)
        cout << i << " ";

    return 0;
}