#include <bits/stdc++.h>

using namespace std;

map<int, vector<int>> adjList;
set<int> visited;
vector<int> path;

bool dfs(int i)
{
    if (visited.count(i) == 1)
    {
        path.push_back(i);
        return true;
    }

    visited.insert(i);
    int parent = (path.size() > 0) ? path.back() : -1;
    path.push_back(i);
    for (int nei : adjList[i])
    {
        if (parent == nei)
            continue;
        if (dfs(nei))
            return true;
    }
    path.pop_back();
    return false;
}

int main()
{
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int src, dest;
        cin >> src >> dest;

        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    bool foundPath = false;

    for (int i = 0; i < N; i++)
    {
        if (visited.count(i) == 0)
        {
            if (dfs(i))
            {
                foundPath = true;
                break;
            }
        }
    }

    if (!foundPath)
        cout << "IMPOSSIBLE" << endl;
    else
    {
        vector<int> actualPath;
        actualPath.push_back(path.back());
        path.pop_back();
        while (actualPath.size() <= 2 || actualPath.back() != actualPath[0])
        {
            actualPath.push_back(path.back());
            path.pop_back();
        }
        cout << actualPath.size() << endl;
        for (auto city : actualPath)
            cout << city << " ";
        cout << endl;
    }
}