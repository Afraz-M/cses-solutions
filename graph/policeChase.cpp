#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
vector<vector<int>> adj;
vector<vector<ll>> capacity;
vector<int> parent;
vector<bool> visited;
queue<int> q;
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
 
int main()
{
    cin >> n >> m;
    adj = vector<vector<int>>(n + 1, vector<int>());
    capacity = vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0));
    parent = vector<int>(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;
        capacity[b][a] = 1;
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
    for(int i = 1; i <= n + 1; i++) {
        bool v = visited[i];
        if(v){
            for(auto nei : adj[i]) {
                if(visited[nei]) continue;
                cout << i << " " << nei << endl;
            }
        }
    }
    cout << endl;
}