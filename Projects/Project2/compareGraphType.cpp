#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <time.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <ctime>

#define MAX_WEIGHT 50
using namespace std;

class PriorityQueue
{
private:
    vector<pair<int, int>> alist;

public:
    void push(pair<int, int> p)
    {
        alist.push_back(p);
        int i = alist.size() - 1;
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (alist[i].first < alist[parent].first)
            {
                swap(alist[i], alist[parent]);
                i = parent;
            }
            else
                break;
        }
    }

    pair<int, int> top()
    {
        return alist[0];
    }

    void pop()
    {
        if (alist.empty())
            return;

        alist[0] = alist.back();
        alist.pop_back();

        int i = 0;

        while (i < alist.size())
        {

            int l = 2 * i + 1, r = 2 * i + 2;
            int smallest = i;

            if (l < alist.size() && alist[l].first < alist[smallest].first)
                smallest = l;
            if (r < alist.size() && alist[r].first < alist[smallest].first)
                smallest = r;

            if (smallest != i)
            {
                swap(alist[i], alist[smallest]);
                i = smallest;
            }
            else
                break;
        }
    }

    bool empty()
    {
        return !alist.size();
    }
};

pair<vector<long>, vector<long>> dijkstraMatPQ(vector<vector<int>> adjMat, int source)
{
    vector<long> visited(adjMat.size(), 0), dist(adjMat.size(), INT_MAX), pi(adjMat.size(), -1);
    PriorityQueue pq;
    int v, u, i;

    dist[source - 1] = 0;
    pq.push({dist[source - 1], source});

    while (!pq.empty())
    {
        v = pq.top().second;
        pq.pop();

        if (visited[v - 1])
            continue;

        visited[v - 1] = 1;

        for (u = 1; u < adjMat.size() + 1; u++)
        {
            if (adjMat[v - 1][u - 1] != 0 && !visited[u - 1] && dist[v - 1] + adjMat[v - 1][u - 1] < dist[u - 1])
            {
                dist[u - 1] = dist[v - 1] + adjMat[v - 1][u - 1];
                pi[u - 1] = v;
                pq.push({dist[u - 1], u});
            }
        }
    }
    return {dist, pi};
}

pair<vector<long>, vector<long>> dijkstraListPQ(vector<vector<pair<int, int>>> adjList, int source)
{
    vector<long> visited(adjList.size(), 0), dist(adjList.size(), INT_MAX), pi(adjList.size(), -1);
    // PriorityQueue pq;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int v, u, w;

    dist[source - 1] = 0;
    pq.push({dist[source - 1], source});

    while (!pq.empty())
    {
        v = pq.top().second;
        pq.pop();

        if (visited[v - 1])
            continue;

        visited[v - 1] = 1;

        for (auto p : adjList[v - 1])
        {
            u = p.first;
            w = p.second;
            if (!visited[u - 1] && dist[v - 1] + w < dist[u - 1])
            {
                dist[u - 1] = dist[v - 1] + w;
                pi[u - 1] = v;
                pq.push({dist[u - 1], u});
            }
        }
    }
    return {dist, pi};
}

pair<vector<long>, vector<long>> dijkstraMatArray(vector<vector<int>> adjMat, int source)
{
    vector<long> visited(adjMat.size(), 0), dist(adjMat.size(), INT_MAX), pi(adjMat.size(), -1);
    int v, u, i;
    int minDist, minVertex;

    dist[source - 1] = 0;
    for (i = 0; i < adjMat.size(); i++)
    {
        minDist = INT_MAX;
        minVertex = -1;
        for (v = 1; v < dist.size() + 1; v++)
        {
            if (!visited[v - 1] && minDist > dist[v - 1])
            {
                minDist = dist[v - 1];
                minVertex = v;
            }
        }
        v = minVertex;
        visited[v - 1] = 1;

        for (u = 1; u < adjMat.size() + 1; u++)
        {
            if (adjMat[v - 1][u - 1] && !visited[u - 1] && dist[v - 1] + adjMat[v - 1][u - 1] < dist[u - 1])
            {
                dist[u - 1] = dist[v - 1] + adjMat[v - 1][u - 1];
                pi[u - 1] = v;
            }
        }
    }
    return {dist, pi};
}

pair<vector<long>, vector<long>> dijkstraListArray(vector<vector<pair<int, int>>> adjList, int source)
{
    vector<long> visited(adjList.size(), 0), dist(adjList.size(), INT_MAX), pi(adjList.size(), -1);
    int v, u, w, i;
    int minDist, minVertex;

    dist[source - 1] = 0;

    for (i = 0; i < adjList.size(); i++)
    {
        minDist = INT_MAX;
        minVertex = -1;
        for (v = 1; v < dist.size() + 1; v++)
        {
            if (!visited[v - 1] && minDist > dist[v - 1])
            {
                minDist = dist[v - 1];
                minVertex = v;
            }
        }
        v = minVertex;
        visited[v - 1] = 1;

        for (auto p : adjList[v - 1])
        {
            u = p.first;
            w = p.second;
            if (!visited[u - 1] && dist[v - 1] + w < dist[u - 1])
            {
                dist[u - 1] = dist[v - 1] + w;
                pi[u - 1] = v;
            }
        }
    }
    return {dist, pi};
}

void graphGenerator(vector<vector<int>> &adjMat, vector<vector<pair<int, int>>> &adjList, int V, long edges)
{
    srand(time(NULL));
    int weight;
    int i, j, k;

    for (k = 0; k < edges; k++)
    {
        do {
            i = rand() % V;
            j = rand() % V;
        } while (adjMat[i][j] != 0 || i == j);

        weight = rand() % MAX_WEIGHT + 1;

        adjMat[i][j] = weight;
        adjMat[j][i] = weight;

        adjList[i].push_back({j + 1, weight});
        adjList[j].push_back({i + 1, weight});
    }
}

void displayAdjMatrix(vector<vector<int>> adjMat, int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            cout << adjMat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void displayAdjList(vector<vector<pair<int, int>>> adjList, int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << (i + 1) << " ";
        for (auto u : adjList[i])
            cout << "\t-> {" << u.first << "," << u.second << "} ";
        cout << endl;
    }
    cout << endl;
}

void displayResults(vector<int> dist, vector<int> pi, int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << "Distance of node " << (i + 1) << " from source is:\t" << dist[i] << "\n";
    }
    for (int i = 0; i < V; i++)
    {
        cout << "Predecessor of node " << (i + 1) << " is:\t" << pi[i] << "\n";
    }
    cout << endl;
}
int main()
{
    // change this V value for different graphs, dont forget to also clean the CSV file
    int V = 500;

    ofstream outputFile("./results/compareSparsity.csv", ios::app);
    vector<long> time_comparisons;

    for (long edges = 100; edges <= V*(V-1)/2; edges += 100)
    {
        vector<vector<int>> adjMat(V, vector<int>(V, 0));
        vector<vector<pair<int, int>>> adjList(V, vector<pair<int, int>>());

        graphGenerator(adjMat, adjList, V, edges);
        // displayAdjList(adjList, V);
        // displayAdjMatrix(adjMat, V);

        cout << "number of edges : " << edges << endl;

        // Dijkstra Matrix Using Array
        auto time1_before = std::chrono::high_resolution_clock::now();
        auto result1 = dijkstraMatPQ(adjMat, 1);
        auto time1_after = std::chrono::high_resolution_clock::now();
        auto time1_difference = chrono::duration_cast<chrono::nanoseconds>(time1_after - time1_before);
        auto dist1 = result1.first;
        auto pi1 = result1.second;
        // displayResults(dist1, pi1, V);
        cout << "(1) time elapsed : " << time1_difference.count() << endl;

        // Dijkstra List Using Priority Queue
        auto time2_before = std::chrono::high_resolution_clock::now();
        auto result2 = dijkstraListPQ(adjList, 1);
        auto time2_after = std::chrono::high_resolution_clock::now();
        auto time2_difference = chrono::duration_cast<chrono::nanoseconds>(time2_after - time2_before);

        auto dist2 = result2.first;
        auto pi2 = result2.second;
        // displayResults(dist2, pi2, V);
        cout << "(2) time elapsed : " << time2_difference.count() << endl;
        cout << endl;

        time_comparisons.push_back(edges);
        time_comparisons.push_back(time1_difference.count());
        time_comparisons.push_back(time2_difference.count());

        int rowsize = time_comparisons.size();

        for (int i = 0; i < rowsize; ++i)
        {
            outputFile << time_comparisons[i];
            if (i < rowsize - 1)
            {
                outputFile << ",";
            }
        }
        outputFile << '\n';

        time_comparisons.clear();
        adjMat.clear();
        adjList.clear();
    }

    return 1;
}