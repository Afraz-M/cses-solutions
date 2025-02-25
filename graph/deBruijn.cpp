#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> path;
vector<bool> vis;

void dfs(int node)
{
    while (!adj[node].empty())
    {
        int v = adj[node].back().first;
        int edge = adj[node].back().second;
        adj[node].pop_back();
        if (vis[edge])
            continue;
        vis[edge] = true;
        dfs(v);
    }
    path.push_back(node);
}

char findchar(int u, int v)
{
    if ((u << 1) % n == v)
        return '0';
    else
        return '1';
}

int main(void)
{
    cin >> n;
    if (n == 1)
    {
        cout << "01" << endl;
        return 0;
    }

    int firstn = n;
    n = (1 << (n - 1));
    m = 2 * n;

    adj = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    vis.resize(m);

    int edgeid = 0;
    for (int i = 0; i < n; i++)
    {
        int oneres = ((i << 1) + 1) % n;
        int zerores = (i << 1) % n;
        adj[i].push_back(make_pair(oneres, edgeid));
        adj[i].push_back(make_pair(zerores, edgeid + 1));
        edgeid += 2;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     cout << i << ": ";
    //     for (auto j : adj[i])
    //     {
    //         cout << j.first << " ";
    //     }
    //     cout << endl;
    // }

    dfs(0);
    reverse(path.begin(), path.end());

    for (int i = 1; i < firstn; i++)
        cout << '0';
    for (int i = 1; i <= m; i++)
    {
        cout << findchar(path[i - 1], path[i]);
    }
    cout << endl;
}