#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <chrono>

using namespace std;

long insertionSort(vector<long> &ar, long l, long r)
{
    long count = 0;
    for (long i = l + 1; i <= r; i++)
    {
        for (long j = i; j > l; j--)
        {
            count++;
            if (ar[j - 1] > ar[j])
                swap(ar[j - 1], ar[j]);
            else
                break;
        }
    }
    return count;
}

long merge(vector<long>& ar, long l, long r) {
    long count = 0;
    long mid = (l + r) / 2;
    long i = l, j = mid + 1;
    vector<long> temp;

    temp.reserve(r - l + 1); // Reserve space in the temporary vector

    while (i <= mid && j <= r) {
        count++;
        if (ar[i] < ar[j]) {
            temp.push_back(ar[i]);
            i++;
        } else {
            temp.push_back(ar[j]);
            j++;
        }
    }

    // Copy any remaining elements from both halves (if any)
    while (i <= mid) {
        temp.push_back(ar[i]);
        i++;
    }
    while (j <= r) {
        temp.push_back(ar[j]);
        j++;
    }

    // Copy the merged data back to the original vector
    std::copy(temp.begin(), temp.end(), ar.begin() + l);

    return count;
}

void mergeSort(vector<long> &ar, long l, long r, long &count)
{
    long mid = (l + r) / 2;

    if (r - l <= 0)
        return;
    else
    {
        mergeSort(ar, l, mid, count);
        mergeSort(ar, mid + 1, r, count);
    }
    count += merge(ar, l, r);
}

void hybridSort(vector<long> &ar, long l, long r, long s, long &count)
{
    long mid = (l + r) / 2;

    if (r - l + 1 <= s)
    {
        count += insertionSort(ar, l, r);
        return;
    }
    else
    {
        hybridSort(ar, l, mid, s, count);
        hybridSort(ar, mid + 1, r, s, count);
    }
    count += merge(ar, l, r);
}

int main()
{
    int choice;

    cout << "input 1 to generate part c(i) csv\n"
         << "input 2 to generate part c(ii) csv\n"
         << "input 3 to generate part d csv\n";

    cin >> choice;

    // vector<long> sizes = {1000, 1206, 1456, 1757, 2120, 2559, 3088, 3727,
    //                       4498, 5428, 6551, 7906, 9540, 11513, 13894, 16768, 20235, 24420, 29470,
    //                       35564, 42919, 51794, 62505, 75431, 91029, 109854, 132571, 159985, 193069,
    //                       232995, 281176, 339322, 409491, 494171, 596362, 719685, 868511, 1048113,
    //                       1264855, 1526417, 1842069, 2222996, 2682695, 3237457, 3906939, 4714866,
    //                       5689866, 6866488, 8286427, 10000000};
    switch (choice)
    {
    case 1:
        // c(i) With the value of S fixed, plot the number of key comparisons over different sizes of the input list n.

        for (long size=5; size<=100000; size += 5)
        {

            ifstream file(("./datasets/" + to_string(size) + ".txt"));
            ofstream outputFile("./results/part_i.csv", ios::app);
            vector<long> ar_hybridsort;
            string line;

            if (!file.is_open())
            {
                cerr << "Failed to open the file." << endl;
                return 1;
            }

            while (getline(file, line))
            {
                stringstream ss(line);
                long entry;

                while (ss >> entry)
                {
                    ar_hybridsort.push_back(entry);

                    if (ss.peek() == ',')
                    {
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

            // chrono::steady_clock::time_point time_before, time_after;
            // chrono::microseconds hybrid_time_difference, mergesort_time_difference;

            // hybrid sort
            auto time_before_hybrid = std::chrono::high_resolution_clock::now();
            hybridSort(ar_hybridsort, 0, size - 1, s, hybridKeyComp);
            auto time_after_hybrid = std::chrono::high_resolution_clock::now();
            auto hybrid_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_hybrid - time_before_hybrid);

            // number of key comparisons and time for hybridSort
            cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;
            cout << "time elapse for hybrid sort: " << hybrid_time_difference.count() << " microseconds" << endl;

            // merge sort
            auto time_before_mergesort = std::chrono::high_resolution_clock::now();
            mergeSort(ar_mergesort, 0, size - 1, mergeKeyComp);
            auto time_after_mergesort = std::chrono::high_resolution_clock::now();
            auto mergesort_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_mergesort - time_before_mergesort);

            // number of key comparisons for mergeSort
            cout << "number of key comparisons for merge sort: " << mergeKeyComp << endl;
            cout << "time elapse for merge sort: " << mergesort_time_difference.count() << " microseconds" << endl;

            cout << endl;

            vector<long> result = {size, hybridKeyComp, mergeKeyComp};
            int rowsize = result.size() + 2;

            for (int i = 0; i < rowsize; ++i)
            {

                if (i < result.size())
                    outputFile << result[i];
                else if (i == 3)
                    outputFile << hybrid_time_difference.count();
                else
                    outputFile << mergesort_time_difference.count();
                // Add a comma after each element except the last one
                if (i < rowsize - 1)
                {
                    outputFile << ",";
                }
            }
            // Add a newline character to separate rows
            outputFile << "\n";

            ar_hybridsort.clear();
            ar_mergesort.clear();
        }
        break;

    case 2:
        // c(ii) With the value of S fixed, plot the number of key comparisons over different sizes of the input list n.

        for (int s=1; s<101; s++)
        {
            long fixed_size = 100000;
            ifstream file(("./datasets/" + to_string(fixed_size) + ".txt"));
            ofstream outputFile("./results/part_ii.csv", ios::app);
            vector<long> ar_hybridsort;
            string line;

            if (!file.is_open())
            {
                cerr << "Failed to open the file." << endl;
                return 1;
            }

            while (getline(file, line))
            {
                stringstream ss(line);
                long entry;

                while (ss >> entry)
                {
                    ar_hybridsort.push_back(entry);

                    if (ss.peek() == ',')
                    {
                        ss.ignore();
                    }
                }
            }

            file.close();
            vector<long> ar_mergesort = ar_hybridsort;
            long hybridKeyComp = 0;
            long mergeKeyComp = 0;

            cout << "s = " << s << endl;

            // chrono::steady_clock::time_point time_before, time_after;
            // chrono::microseconds hybrid_time_difference, mergesort_time_difference;

            // hybrid sort
            auto time_before_hybrid = std::chrono::high_resolution_clock::now();
            hybridSort(ar_hybridsort, 0, fixed_size - 1, s, hybridKeyComp);
            auto time_after_hybrid = std::chrono::high_resolution_clock::now();
            auto hybrid_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_hybrid - time_before_hybrid);

            // number of key comparisons and time for hybridSort
            cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;
            cout << "time elapse for hybrid sort: " << hybrid_time_difference.count() << " microseconds" << endl;

            // merge sort
            auto time_before_mergesort = std::chrono::high_resolution_clock::now();
            mergeSort(ar_mergesort, 0, fixed_size - 1, mergeKeyComp);
            auto time_after_mergesort = std::chrono::high_resolution_clock::now();
            auto mergesort_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_mergesort - time_before_mergesort);

            // number of key comparisons for mergeSort
            cout << "number of key comparisons for merge sort: " << mergeKeyComp << endl;
            cout << "time elapse for merge sort: " << mergesort_time_difference.count() << " microseconds" << endl;

            cout << endl;

            vector<long> result = {s, hybridKeyComp, mergeKeyComp};
            int rowsize = result.size() + 2;

            for (int i = 0; i < rowsize; ++i)
            {

                if (i < result.size())
                    outputFile << result[i];
                else if (i == 3)
                    outputFile << hybrid_time_difference.count();
                else
                    outputFile << mergesort_time_difference.count();
                // Add a comma after each element except the last one
                if (i < rowsize - 1)
                {
                    outputFile << ",";
                }
            }
            // Add a newline character to separate rows
            outputFile << "\n";

            ar_hybridsort.clear();
            ar_mergesort.clear();
        }
        break;

    case 3:
        // part d
        long final_size = 10000000;
        int optimal_s = 7;

        ifstream file(("./datasets/10000000.txt"));
        ofstream outputFile("./results/part_d.csv", ios::app);
        vector<long> ar_hybridsort;
        string line;

        if (!file.is_open())
        {
            cerr << "Failed to open the file." << endl;
            return 1;
        }

        while (getline(file, line))
        {
            stringstream ss(line);
            long entry;

            while (ss >> entry)
            {
                ar_hybridsort.push_back(entry);

                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
        }

        file.close();
        vector<long> ar_mergesort = ar_hybridsort;
        long hybridKeyComp = 0;
        long mergeKeyComp = 0;

        // chrono::steady_clock::time_point time_before, time_after;
        // chrono::microseconds hybrid_time_difference, mergesort_time_difference;

        cout << "using size: " << final_size << endl;

        // hybrid sort
        auto time_before_hybrid = std::chrono::high_resolution_clock::now();
        hybridSort(ar_hybridsort, 0, final_size - 1, optimal_s, hybridKeyComp);
        auto time_after_hybrid = std::chrono::high_resolution_clock::now();
        auto hybrid_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_hybrid - time_before_hybrid);

        // number of key comparisons and time for hybridSort
        cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;
        cout << "time elapse for hybrid sort: " << hybrid_time_difference.count() << " microseconds" << endl;

        // merge sort
        auto time_before_mergesort = std::chrono::high_resolution_clock::now();
        mergeSort(ar_mergesort, 0, final_size - 1, mergeKeyComp);
        auto time_after_mergesort = std::chrono::high_resolution_clock::now();
        auto mergesort_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_mergesort - time_before_mergesort);

        // number of key comparisons for mergeSort
        cout << "number of key comparisons for merge sort: " << mergeKeyComp << endl;
        cout << "time elapse for merge sort: " << mergesort_time_difference.count() << " microseconds" << endl;

        cout << endl;

        vector<long> result = {optimal_s, hybridKeyComp, mergeKeyComp};
        int rowsize = result.size() + 2;

        for (int i = 0; i < rowsize; ++i)
        {

            if (i < result.size())
                outputFile << result[i];
            else if (i == 3)
                outputFile << hybrid_time_difference.count();
            else
                outputFile << mergesort_time_difference.count();
            // Add a comma after each element except the last one
            if (i < rowsize - 1)
            {
                outputFile << ",";
            }
        }
        // Add a newline character to separate rows
        outputFile << "\n";

        ar_hybridsort.clear();
        ar_mergesort.clear();

        break;
    }

    return 1;
}