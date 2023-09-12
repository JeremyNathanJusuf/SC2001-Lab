#include <iostream>
#include <vector>
using namespace std;

void swap(int& n, int& m) {
    int temp = n;
    n = m;
    m = temp;
}

void insertionSort(vector<int>& ar, int l, int r) {
    for (int i=l+1; i<=r; i++) {
        for (int j=i; j>l; j--) {
            if (ar[j-1] > ar[j]) 
                swap(ar[j-1], ar[j]);
            else break;
        }
    }
}

void merge(vector<int>& ar, int l, int r) {
    int mid = (l+r)/2;
    int i=l, j=mid+1;

    while (i <= mid && j <= r) {
        if (ar[i] < ar[j]) i++;
        else if (ar[i] > ar[j]) {
            ar.insert(ar.begin() + i, ar[j]);
            ar.erase(ar.begin() + j + 1);
            i++; j++; mid++;
        }
        else {
            ar.insert(ar.begin() + i+1, ar[j]);
            ar.erase(ar.begin() + j + 1);
            i+=2; j++; mid++;
        }
    }
}

void hybridSort(vector<int>& ar, int l, int r, int s) {
    int mid = (l+r)/2;
    
    if (r - l + 1 <= s) insertionSort(ar, l, r);
    else {
        hybridSort(ar, l, mid, s);
        hybridSort(ar, mid+1, r, s);
    }
    merge(ar, l, r);
}

int main() {
    vector<int> ar = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};
    
    //before sort
    for (int i : ar)
        cout << i << " ";
    cout << endl;

    //hybrid sort
    hybridSort(ar, 0, 11, 3);

    //after sort
    for (int i : ar)
        cout << i << " ";

    return 0;
}