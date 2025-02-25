#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
vector<set<int>> adj;
vector<vector<ll>> capacity;
vector<int> parent;
vector<bool> visited;
queue<int> q;
int n, m;
 
bool bfs()
{
    visited = vector<bool>(n + 2, false);
    q = queue<int>();
    q.push(0);
    visited[0] = true;
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
    return visited[n + 1];
}
 
int main()
{
    int n1, n2;
    cin >> n1 >> n2 >> m;
    n = n1 + n2;
 
    adj = vector<set<int>>(n + 2, set<int>());
    capacity = vector<vector<ll>>(n + 2, vector<ll>(n + 2, 0));
    parent = vector<int>(n + 2, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        b += n1;
 
        adj[a].insert(b);
        adj[b].insert(a);
        capacity[a][b] = 1;
    }
 
    for (int i = 1; i <= n1; i++)
    {
        adj[0].insert(i);
        adj[i].insert(0);
        capacity[0][i] = 1;
    }
 
    for (int i = n1 + 1; i <= n; i++)
    {
        adj[n + 1].insert(i);
        adj[i].insert(n + 1);
        capacity[i][n + 1] = 1;
    }
 
    ll ans = 0;
    while (bfs())
    {
        ll pathflow = LLONG_MAX;
        int s = n + 1;
        while (s != 0)
        {
            pathflow = min(pathflow, capacity[parent[s]][s]);
            s = parent[s];
        }
 
        ans += pathflow;
        int v = n + 1;
        while (v != 0)
        {
            int u = parent[v];
            capacity[u][v] -= pathflow;
            capacity[v][u] += pathflow;
            v = parent[v];
        }
    }
 
    cout << ans << endl;
    for (int boy = 1; boy <= n1; boy++)
    {
        for (auto girl : adj[boy])
        {
            if (capacity[boy][girl] == 0)
            {
                if (girl == 0)
                    continue;
                cout << boy << " " << girl - n1 << endl;
            }
        }
    }
}