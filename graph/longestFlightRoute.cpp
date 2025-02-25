#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjList;
vector<int> dp;
vector<bool> vis;
int N, M;

int dfs(int i)
{
    if (vis[i])
        return dp[i];

    vis[i] = true;

    for (auto nei : adjList[i])
    {
        if (dfs(nei) == -1)
            continue;
        dp[i] = max(dp[i], 1 + dfs(nei));
    }

    return dp[i];
}

int next_node(int i)
{
    int nextnode;
    int nodelen = -2;
    for (auto v : adjList[i])
    {
        if (dp[v] > nodelen)
        {
            nodelen = dp[v];
            nextnode = v;
        }
    }
    return nextnode;
}

int main(void)
{
    cin >> N >> M;
    adjList = vector<vector<int>>(N + 1, vector<int>());
    dp = vector<int>(N + 1, -1);
    vis = vector<bool>(N + 1, false);
    dp[N] = 0;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    dfs(1);

    if (dp[1] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    int curr = 1;
    cout << dp[curr] + 1 << endl;
    while (curr != N)
    {
        cout << curr << " ";
        curr = next_node(curr);
    }
    cout << curr << endl;
}