#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
int n, m;
vector<vector<int>> adjList;
vector<vector<int>> adjListR;
vector<bool> can1;
vector<bool> canx;
 
void dfs1(int root)
{
    if (can1[root])
        return;
    can1[root] = true;
 
    for (auto nei : adjList[root])
        dfs1(nei);
}
 
void dfsx(int root)
{
    if (canx[root])
        return;
    canx[root] = true;
 
    for (auto nei : adjListR[root])
        dfsx(nei);
}
 
int main()
{
    cin >> n >> m;
 
    adjList = vector<vector<int>>(n + 1, vector<int>());
    adjListR = vector<vector<int>>(n + 1, vector<int>());
    can1 = vector<bool>(n + 1, false);
    canx = vector<bool>(n + 1, false);
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjListR[b].push_back(a);
    }
 
    dfs1(1);
    dfsx(1);
 
    for (int i = 1; i <= n; i++)
    {
        if (!canx[i])
        {
            cout << "NO" << endl;
            cout << i << " " << 1 << endl;
            return 0;
        }
        if (!can1[i])
        {
            cout << "NO" << endl;
            cout << 1 << " " << i << endl;
            return 0;
        }
    }
 
    cout << "YES";
}