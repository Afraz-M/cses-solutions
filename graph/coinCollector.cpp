#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
int n, m;
 
vector<vector<int>> adjList;
vector<vector<int>> radjList;
vector<bool> visited;
vector<int> caveSCC;
vector<long long> coins;
priority_queue<pair<int, int>> pq;
vector<ll> sccCoins;
vector<set<int>> sccAdjList;
vector<pair<int, int>> edges;
vector<ll> table;
 
int mytime = 0;
 
void krdfs1(int root)
{
    if (visited[root])
        return;
    mytime += 1;
    visited[root] = true;
 
    for (auto nei : adjList[root])
        krdfs1(nei);
 
    mytime += 1;
    pq.push(make_pair(mytime, root));
}
 
ll krdfs2(int root, int sccid)
{
    if (visited[root])
        return 0;
    visited[root] = true;
 
    ll retval = coins[root];
    caveSCC[root] = sccid;
    for (auto nei : radjList[root])
        retval += krdfs2(nei, sccid);
 
    return retval;
}
 
ll dp(int root)
{
    if (table[root] != 0)
        return table[root];
 
    ll retval = 0;
    for (auto nei : sccAdjList[root])
    {
        retval = max(retval, dp(nei));
    }
 
    table[root] = retval + sccCoins[root];
    return table[root];
}
 
int main()
{
    cin >> n >> m;
 
    adjList = vector<vector<int>>(n + 1, vector<int>());
    radjList = vector<vector<int>>(n + 1, vector<int>());
    coins = vector<long long>(n + 1, 0);
    visited = vector<bool>(n + 1, false);
    caveSCC = vector<int>(n + 1, 0);
    sccCoins = vector<ll>(n + 1, 0);
 
    for (int i = 1; i <= n; i++)
    {
        cin >> coins[i];
    }
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        radjList[b].push_back(a);
        edges.push_back(make_pair(a, b));
    }
 
    for (int i = 1; i <= n; i++)
        krdfs1(i);
 
    visited = vector<bool>(n + 1, false);
    int sccid = 1;
    while (!pq.empty())
    {
        int root = pq.top().second;
        pq.pop();
        if (visited[root])
            continue;
        sccCoins[sccid] = krdfs2(root, sccid);
        sccid += 1;
    }
 
    int sccCount = sccid -= 1;
    sccAdjList = vector<set<int>>(sccCount + 1, set<int>());
    table = vector<ll>(sccCount + 1, 0);
    for (auto edge : edges)
    {
        int a = edge.first;
        int b = edge.second;
        if (caveSCC[a] == caveSCC[b])
            continue;
        sccAdjList[caveSCC[a]].insert(caveSCC[b]);
    }
 
    for (int i = 1; i <= sccCount; i++)
    {
        dp(i);
    }
 
    cout << *max_element(table.begin(), table.end()) << endl;
}