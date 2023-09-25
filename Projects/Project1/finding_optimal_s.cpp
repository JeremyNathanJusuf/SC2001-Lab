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

long merge(vector<long> &ar, long l, long r)
{
    long count = 0;
    long mid = (l + r) / 2;
    long i = l, j = mid + 1;
    vector<long> temp;

    temp.reserve(r - l + 1); // Reserve space in the temporary vector

    while (i <= mid && j <= r)
    {
        count++;
        if (ar[i] < ar[j])
        {
            temp.push_back(ar[i]);
            i++;
        }
        else
        {
            temp.push_back(ar[j]);
            j++;
        }
    }

    // Copy any remaining elements from both halves (if any)
    while (i <= mid)
    {
        temp.push_back(ar[i]);
        i++;
    }
    while (j <= r)
    {
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
    vector<long> result;
    ofstream outputFile("./results/finding_optimal_s.csv", ios::app);
    for (long size = 1000; size <= 101000; size += 5000) result.push_back(size);
    int rowsize = result.size();

        outputFile << "S values,";

        for (int i = 0; i < rowsize; ++i)
        {

            if (i < result.size())
                outputFile << result[i];

            // Add a comma after each element except the last one
            if (i < rowsize - 1)
            {
                outputFile << ",";
            }
        }
        // Add a newline character to separate rows
        outputFile << "\n";

        result.clear();

    for (long s = 2; s <= 60; s+=2)
    {
        result.push_back(s);

        for (long size = 1000; size <= 101000; size += 5000)
        {
            ifstream file(("./datasets/" + to_string(size) + ".txt"));
            
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
            long hybridKeyComp = 0;

            cout << "sorting data with size " << size << endl;
            cout << "s = " << s << endl;

            // hybrid sort
            auto time_before_hybrid = std::chrono::high_resolution_clock::now();
            hybridSort(ar_hybridsort, 0, size - 1, s, hybridKeyComp);
            auto time_after_hybrid = std::chrono::high_resolution_clock::now();
            auto hybrid_time_difference = chrono::duration_cast<chrono::microseconds>(time_after_hybrid - time_before_hybrid);

            // number of key comparisons and time for hybridSort
            cout << "number of key comparisons for hybrid sort: " << hybridKeyComp << endl;
            cout << "time elapse for hybrid sort: " << hybrid_time_difference.count() << " microseconds" << endl;

            ar_hybridsort.clear();

            result.push_back(hybrid_time_difference.count());
        }
        
        
        int rowsize = result.size();

        for (int i = 0; i < rowsize; ++i)
        {

            if (i < result.size())
                outputFile << result[i];

            // Add a comma after each element except the last one
            if (i < rowsize - 1)
            {
                outputFile << ",";
            }
        }
        // Add a newline character to separate rows
        outputFile << "\n";

        result.clear();
    }

    return 1;
}