#include <iostream>
#include <vector>
using namespace std;

void print1DMemo(vector<int> memo) {
    cout << "Memo: " << endl;

    for (int i = 1; i < memo.size(); i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 1; i < memo.size(); i++) {
        cout << memo[i] << "\t";
    }
    cout << endl;
}

int knapsack(vector<int> w, vector<int> p, int capacity) {
    int n = w.size();
    vector<int>profit(capacity+1, 0);

    for (int i = 1; i <= capacity; i++) {
        for (int j = 0; j < n; j++) {
            if (w[j] <= i) {
            profit[i] = max(profit[i], profit[i-w[j]] + p[j]);
            }
        }
    }

    print1DMemo(profit);

    return profit[capacity];
}

int main() {
    vector<int> w1 = {4,6,8}, p1 = {7,6,9};
    int capacity1 = 14;
    vector<int> w2 = {5,6,8}, p2 = {7,6,9};
    int capacity2 = 14;
    

    cout << "Part 4a" << endl;
    cout << "Weights: " << endl;
    for (int i = 0; i < w1.size(); i++) {
        cout << w1[i] << " ";
    }
    cout << endl;

    cout << "Profits: " << endl;
    for (int i = 0; i < p1.size(); i++) {
        cout << p1[i] << " ";
    }
    cout << endl;

    cout << "Capacity: " << capacity1 << endl << endl;

    int result1 = knapsack(w1, p1, capacity1);

    cout << "Max profit: " <<  result1 << endl << endl;

    

    cout << "Part 4b" << endl;
    cout << "Weights: " << endl;
    for (int i = 0; i < w2.size(); i++) {
        cout << w2[i] << " ";
    }
    cout << endl;

    cout << "Profits: " << endl;
    for (int i = 0; i < p2.size(); i++) {
        cout << p2[i] << " ";
    }
    cout << endl;

    cout << "Capacity: " << capacity2 << endl << endl;

    int result2 = knapsack(w2, p2, capacity1);

    cout << "Max profit: " <<  result2 << endl << endl;


    return 1;
}