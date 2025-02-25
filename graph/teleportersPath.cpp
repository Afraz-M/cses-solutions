#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> path;
vector<bool> vis;

void dfs(int node)
{
    while (!g[node].empty())
    {
        int v = g[node].back().first;
        int edge = g[node].back().second;
        g[node].pop_back();
        if (vis[edge])
            continue;
        vis[edge] = true;
        dfs(v);
    }
    path.push_back(node);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);
    g.resize(n);
    vis.resize(m);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].push_back({y, i});
        // g[y].push_back({x, i});
        outdegree[x]++, indegree[y]++;
    }

    if (outdegree[0] - indegree[0] != 1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    if (indegree[n - 1] - outdegree[n - 1] != 1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (int i = 1; i < n - 1; i++)
    {
        if (indegree[i] != outdegree[i])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    // for (int i = 0; i < n; i++)
    // {
    //     if (degree[i] % 2)
    //     {
    //         cout << "IMPOSSIBLE" << '\n';
    //         return 0;
    //     }
    // }

    dfs(0);

    if (path.size() != m + 1)
        cout << "IMPOSSIBLE" << '\n';
    else
    {
        while (!path.empty())
        {
            cout << path.back() + 1 << " ";
            path.pop_back();
        }
        cout << endl;
    }
    return 0;
}