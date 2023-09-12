#include <iostream>
using namespace std;

void shiftOneRight(int* ar, int a, int b) {
    int cur = ar[a], next;
    for (int i=a; i<=b; i++) {
        next = ar[i+1];
        ar[i+1] = cur;
        cur = next;
    }
}

void merge(int* ar, int n, int m) {
    int mid = (n+m)/2;
    int i=n, j=mid+1, temp;

    while (i <= mid && j <= m) {
        if (ar[i] < ar[j]) {
            i++;
        }
        else if (ar[i] > ar[j]) {
            temp = ar[j];
            shiftOneRight(ar, i, mid);
            ar[i] = temp;
            i++; j++; mid++;
        }
        else {
            shiftOneRight(ar, i, mid);
            i+=2; mid++; j++;
        }
    }
}

void mergeSort(int* ar, int n, int m) {
    int mid = (n+m)/2;

    if (m - n<= 0) 
        return;

    else if (m - n > 1) {
        mergeSort(ar, n, mid);
        mergeSort(ar, mid+1, m);
    }

    merge(ar, n, m);
}

int main() {
    int ar[] = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};
    
    for (int i : ar)
        cout << i << " ";
    cout << endl;

    mergeSort(ar, 0, 11);
    for (int i : ar)
        cout << i << " ";

    return 0;
}