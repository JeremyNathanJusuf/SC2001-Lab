#include <iostream>
using namespace std;

int aux[100];

void merge(int* ar, int n, int m) {
    int mid = (n+m)/2;

    if (m - n <= 0) 
        return;
    
    int l1 = mid - n + 1;
    int l2 = m - mid;
    int* t1 = (int*)malloc(sizeof(int) * l1);
    int* t2 = (int*)malloc(sizeof(int) * l2);

    for (int i=0; i<l1; i++) t1[i] = ar[n + i];
    for (int j=0; j<l2; j++) t2[j] = ar[mid + 1 + j];

    int i = 0, j = 0, k = n;
    
    while (i < l1 && j < l2) {
        if (t1[i] <= t2[j]) ar[k++] = t1[i++];
        else ar[k++] = t2[j++];
    }
    
    while (i < l1) {
        ar[k++] = t1[i++];
    }

    while (j < l2) {
        ar[k++] = t2[j++];
    }
}

void merge1(int* ar, int n, int m) {
    int mid =(n+m)/2;
    int l1 = mid - n + 1;
    int l2 = m - mid;
    int i, j ,k;

    for (i=n; i<=m; i++) aux[i] = ar[i];

    i = n; j = n; k = mid+1;

    while (j <= mid && k <= m) {
        if (aux[j] <= aux[k]) ar[i++] = aux[j++];
        else ar[i++] = aux[k++];
    }

    while (j <= mid) ar[i++] = aux[j++];
    while (k <= m) ar[i++] = aux[k++];
}

void mergeSort(int* ar, int n, int m) {
    int mid = (n+m)/2;

    if (m - n<= 0) 
        return;

    else if (m - n > 1) {
        mergeSort(ar, n, mid);
        mergeSort(ar, mid+1, m);
    }

    merge1(ar, n, m);
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