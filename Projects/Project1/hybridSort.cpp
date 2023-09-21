#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <chrono>

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
    
    if (r - l + 1 <= s) {
        count += insertionSort(ar, l, r); 
        return;
    }
    else {
        hybridSort(ar, l, mid, s, count);
        hybridSort(ar, mid+1, r, s, count);
    }
    count += merge(ar, l, r);
}

int main() {
    // (c) Analyze time complexity

    // (i) With the value of S fixed, plot the number of key comparisons over different sizes of the input list n.
    vector<long> sizes = {1000, 1206, 1456, 1757, 2120, 2559, 3088, 3727,
    4498, 5428, 6551, 7906, 9540, 11513, 13894, 16768, 20235, 24420, 29470, 
    35564, 42919, 51794, 62505, 75431, 91029, 109854, 132571, 159985, 193069, 
    232995, 281176, 339322, 409491, 494171, 596362, 719685, 868511, 1048113, 
    1264855, 1526417, 1842069, 2222996, 2682695, 3237457, 3906939, 4714866, 
    5689866, 6866488, 8286427, 10000000};  

    for(long size : sizes) {

        ifstream file(("./datasets/" + to_string(size) + ".txt"));
        ofstream outputFile("./results/part_i.csv", ios::app);
        vector<long> ar_hybridsort;
        string line;
        

        if (!file.is_open()) {
            cerr << "Failed to open the file." << endl;
            return 1;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            long entry;

            while (ss >> entry) {
                ar_hybridsort.push_back(entry);

                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
        }
        
        file.close();
        vector<long> ar_mergesort = ar_hybridsort;
        long hybridKeyComp = 0;
        long mergeKeyComp = 0;
        int s = 5;

        cout << "sorting data with size " << size << endl; 
        cout << "s = " << s << endl;

        //chrono::steady_clock::time_point time_before, time_after;
        //chrono::microseconds hybrid_time_difference, mergesort_time_difference;
        

        //hybrid sort
        auto time_before_hybrid = std::chrono::high_resolution_clock::now();
        hybridSort(ar_hybridsort, 0, size-1, s, hybridKeyComp);
        auto time_after_hybrid = std::chrono::high_resolution_clock::now(); 
        auto hybrid_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_hybrid - time_before_hybrid);

        //number of key comparisons and time for hybridSort
        cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;
        cout << "time elapse for hybrid sort: " << hybrid_time_difference.count() << " microseconds" << endl;


        //merge sort
        auto time_before_mergesort = std::chrono::high_resolution_clock::now();
        mergeSort(ar_mergesort, 0, size-1, mergeKeyComp);
        auto time_after_mergesort = std::chrono::high_resolution_clock::now();
        auto mergesort_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_mergesort - time_before_mergesort);

        //number of key comparisons for mergeSort
        cout << "number of key comparisons for merge sort: " << mergeKeyComp << endl;
        cout << "time elapse for merge sort: " << mergesort_time_difference.count() << " microseconds" << endl;

        cout << endl;

        vector<long> result = {size, hybridKeyComp, mergeKeyComp};
        int rowsize = result.size() + 2;
        
            for (int i = 0; i < rowsize; ++i) {

                if (i < result.size())
                    outputFile << result[i];
                else if (i == 3)
                    outputFile << hybrid_time_difference.count();
                else 
                    outputFile << mergesort_time_difference.count();
                // Add a comma after each element except the last one
                if (i < rowsize - 1) {
                    outputFile << ",";
                }
            }
            // Add a newline character to separate rows
            outputFile << "\n";
            

    }
    return 1;   
}