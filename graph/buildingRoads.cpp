#include <bits/stdc++.h>

using namespace std;

map<int, set<int>> adjList;
set<int> visited;
vector<int> roots;
int N, M;

void dfs(int i)
{
    if (visited.count(i) == 1)
        return;

    visited.insert(i);

    for (int nei : adjList[i])
    {
        dfs(nei);
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int src, dest;
        cin >> src >> dest;
        adjList[src].insert(dest);
        adjList[dest].insert(src);
    }

    for (int i = 1; i <= N; i++)
    {
        if (visited.count(i) == 1)
            continue;

        roots.push_back(i);
        dfs(i);
    }

    cout << roots.size() - 1 << endl;
    int times = roots.size() - 1;

    for (int i = 0; i < times; i++)
    {
        cout << roots[i] << ' ' << roots[i + 1] << endl;
    }
}