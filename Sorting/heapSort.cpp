#include <iostream>
#include <vector>
using namespace std;

void fixHeap(vector<int>& ar, int n, int i) {
    int l = 2*i, r = 2*i+1;
    int largest = i;

    if (l <= n && ar[largest] < ar[l]) 
        largest = l;
    
    if (r <= n && ar[largest] < ar[r]) 
        largest = r;
    
    if (largest != i) {
        swap(ar[largest], ar[i]);
        fixHeap(ar, n, largest);
    }
}

void heapifying(vector<int>& ar, int n, int i) {
    int l = 2*i, r = 2*i+1;

    if (l <= n) 
        heapifying(ar, n, l);
    if (r <= n)
        heapifying(ar, n, r);

    fixHeap(ar, n, i);
}

void constructHeap(vector<int>& ar) {
    ar.insert(ar.begin(), -1);
    heapifying(ar, ar.size()-1, 1);
}

void fixToArray(vector<int>& ar) {
    ar.erase(ar.begin());
}

int deleteMax(vector<int>& ar, int n) {
    int max = ar[1];
    int lowerRight = ar[n];
    ar.erase(ar.begin()+1);
    ar.insert(ar.begin()+1, lowerRight);

    fixHeap(ar, n-1, 1);
    return max;
}

void heapSort(vector<int>& ar) {
    int curMax, n = ar.size();
    constructHeap(ar);

    for (int i=n; i>0; i--) {
        curMax = deleteMax(ar, i);
        ar[i] = curMax;
    }

    fixToArray(ar);
}

int main() {
    vector<int> ar = {45, 29, 64, 12, 100, 21, 1000, 32, 21, 21, 101, 989};

    for (int i : ar)
        cout << i << " ";
    cout << endl;

    heapSort(ar);

    for (int i : ar)
        cout << i << " ";

    return 0;
}