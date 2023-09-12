#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& ar, int l, int r) {
    int lastSmall = l, pivot = ar[l];

    for (int i=l+1; i<=r; i++) {
        if (pivot > ar[i]) {
            swap(ar[++lastSmall], ar[i]);
        }
    }
    swap(ar[lastSmall], ar[l]);
    return lastSmall;
}

void quickSort(vector<int>& ar, int l, int r) {
    int pivotIndex;
    if (l >= r) return;
    pivotIndex = partition(ar, l, r);
    quickSort(ar, l, pivotIndex-1);
    quickSort(ar, pivotIndex+1, r);
}

int main() {
    vector<int> ar = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};
    
    for (int i : ar)
        cout << i << " ";
    cout << endl;

    quickSort(ar, 0, 11);

    for (int i : ar)
        cout << i << " ";

    return 0;
}