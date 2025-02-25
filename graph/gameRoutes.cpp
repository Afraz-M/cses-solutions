#include <bits/stdc++.h>

using namespace std;

int N, M;
long long MODVAL = powl(10, 9) + 7;
vector<vector<int>> adjList;
vector<long long> dp;

int dfs(int i)
{
    if (dp[i] != -1)
        return dp[i];
    long long ans = 0;
    for (auto nei : adjList[i])
    {
        ans += (dfs(nei)) % MODVAL;
        ans = ans % MODVAL;
    }
    dp[i] = ans;
    return dp[i];
}

int main(void)
{
    cin >> N >> M;
    adjList = vector<vector<int>>(N + 1, vector<int>());
    dp = vector<long long>(N + 1, -1);
    dp[N] = 1;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    cout << dfs(1) << endl;
}