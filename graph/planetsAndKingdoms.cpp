#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
int n, m;
vector<vector<int>> adjList;
vector<vector<int>> adjList2;
stack<int> st;
vector<bool> visited;
priority_queue<pair<int, int>> pq;
vector<int> nodetokingdom;
int mytime;
 
void dfs(int root)
{
    if (visited[root])
        return;
 
    mytime += 1;
    visited[root] = true;
 
    for (auto nei : adjList[root])
    {
        dfs(nei);
    }
 
    mytime += 1;
    pq.push(make_pair(mytime, root));
}
 
void dfs2(int root, int kingdom)
{
    if (visited[root])
        return;
    visited[root] = true;
 
    nodetokingdom[root] = kingdom;
    for (auto nei : adjList2[root])
    {
        dfs2(nei, kingdom);
    }
}
 
int main()
{
    cin >> n >> m;
    adjList = vector<vector<int>>(n + 1, vector<int>());
    adjList2 = vector<vector<int>>(n + 1, vector<int>());
    visited = vector<bool>(n + 1, false);
    nodetokingdom = vector<int>(n + 1, 0);
    mytime = 0;
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList2[b].push_back(a);
    }
 
    for (int i = 1; i <= n; i++)
    {
        dfs(i);
    }
 
    visited = vector<bool>(n + 1, false);
    int kingdom = 1;
    while (!pq.empty())
    {
        int root = pq.top().second;
        pq.pop();
        if (visited[root])
            continue;
        dfs2(root, kingdom);
        kingdom += 1;
    }
 
    cout << kingdom - 1 << endl;
    nodetokingdom.erase(nodetokingdom.begin());
    for (auto k : nodetokingdom)
    {
        cout << k << " ";
    }
    cout << endl;
}