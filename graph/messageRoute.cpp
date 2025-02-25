#include <bits/stdc++.h>

using namespace std;

int N, M;
map<int, vector<int>> adjList;
map<int, int> parent;
queue<int> q;
set<int> visited;

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int src, dest;
        cin >> src >> dest;
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    q.push(1);
    visited.insert(1);
    bool foundPath = false;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (curr == N)
        {
            foundPath = true;
            break;
        }

        for (int nei : adjList[curr])
        {
            if (visited.count(nei) == 1)
                continue;

            q.push(nei);
            parent[nei] = curr;
            visited.insert(nei);
        }
    }

    if (!foundPath)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<int> path;
    int curr = N;
    path.push_back(curr);

    while (curr != 1)
    {
        curr = parent[curr];
        path.push_back(curr);
    }

    int times = path.size();
    cout << times << endl;
    for (int i = 0; i < times; i++)
    {
        cout << path.back() << " ";
        path.pop_back();
    }
    cout << endl;
}