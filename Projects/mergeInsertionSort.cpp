#include <iostream>
#include <vector>
using namespace std;

long insertionSort(vector<long>& ar, long l, long r) {
    long count = 0;
    for (long i=l+1; i<=r; i++) {
        for (long j=i; j>l; j--) {
            count++;
            if (ar[j-1] > ar[j]) 
                swap(ar[j-1], ar[j]);
            else break;
        }
    }
    return count;
}

long merge(vector<long>& ar, long l, long r) {
    long count = 0;
    long mid = (l+r)/2;
    long i=l, j=mid+1;

    while (i <= mid && j <= r) {
        count++;
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

    return count;
}

void mergeSort(vector<long>& ar, long l, long r, long& count) {
    long mid = (l+r)/2;
    
    if (r - l <= 0) return;
    else {
        mergeSort(ar, l, mid, count);
        mergeSort(ar, mid+1, r, count);
    }
    count += merge(ar, l, r);
}

void hybridSort(vector<long>& ar, long l, long r, long s, long& count) {
    long mid = (l+r)/2;
    
    if (r - l + 1 <= s) count += insertionSort(ar, l, r);
    else {
        hybridSort(ar, l, mid, s, count);
        hybridSort(ar, mid+1, r, s, count);
    }
    count += merge(ar, l, r);
}

int main() {
    vector<long> ar = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};
    long size = ar.size();
    long hybridKeyComp = 0;
    long mergeKeyComp = 0;

    //before sort
    for (long i : ar)
        cout << i << " ";
    cout << endl;


    //hybrid sort
    hybridSort(ar, 0, size-1, 5, hybridKeyComp);

    //number of key comparisons for hybridSort
    cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;


    //merge sort
    mergeSort(ar, 0, size-1, mergeKeyComp);

    //number of key comparisons for mergeSort
    cout << "number of key comparisons for merge sort: " << mergeKeyComp << endl;


    //after sort
    for (long i : ar)
        cout << i << " ";

    return 0;
}