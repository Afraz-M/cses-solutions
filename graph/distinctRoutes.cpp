#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<vector<pair<int, int>>> graph;
vector<vector<ll>> capacity;
vector<int> parent;
vector<bool> visited;
queue<int> q;
vector<int> path;
set<int> edgesDone;
int n, m;

bool bfs()
{
    visited = vector<bool>(n + 1, false);
    q = queue<int>();
    q.push(1);
    visited[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : adj[u])
        {
            if (capacity[u][v] <= 0 || visited[v])
                continue;
            q.push(v);
            visited[v] = true;
            parent[v] = u;
        }
    }
    return visited[n];
}

bool dfs(int root)
{
    if (visited[root])
        return false;

    visited[root] = true;
    path.push_back(root);
    if (root == n)
        return true;

    for (auto val : graph[root])
    {
        if (edgesDone.count(val.second) || capacity[root][val.first] != 0)
            continue;
        edgesDone.insert(val.second);
        if (dfs(val.first))
            return true;
    }
    path.pop_back();
    return false;
}

int main()
{
    cin >> n >> m;
    adj = vector<vector<int>>(n + 1, vector<int>());
    graph = vector<vector<pair<int, int>>>(n + 1, vector<pair<int, int>>());
    capacity = vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0));
    parent = vector<int>(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        graph[a].push_back(make_pair(b, i));
        capacity[a][b] += 1;
    }

    ll ans = 0;
    while (bfs())
    {
        ll pathflow = LLONG_MAX;
        int s = n;
        while (s != 1)
        {
            pathflow = min(pathflow, capacity[parent[s]][s]);
            s = parent[s];
        }
        ans += pathflow;
        int v = n;
        while (v != 1)
        {
            int u = parent[v];
            capacity[u][v] -= pathflow;
            capacity[v][u] += pathflow;
            v = parent[v];
        }
    }
    cout << ans << endl;

    for (int i = 0; i < ans; i++)
    {
        path = vector<int>();
        visited = vector<bool>(n + 1, false);
        dfs(1);
        cout << path.size() << endl;
        for (auto p : path)
            cout << p << " ";
        cout << endl;
    }
}