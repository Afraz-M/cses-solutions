#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
ll MODVAL = 1e9 + 7;
 
int n, m;
vector<vector<int>> adjList;
ll dp[1 << 20][20];
 
int main(void)
{
    cin >> n >> m;
    adjList = vector<vector<int>>(n + 1, vector<int>());
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[--b].push_back(--a);
    }
 
    dp[1][0] = 1;
    for (int s = 2; s < 1 << n; s++)
    {
        if ((s & (1 << 0)) == 0)
            continue;
 
        if ((s & (1 << (n - 1))) && s != ((1 << n) - 1))
            continue;
 
        for (int end = 0; end < n; end++)
        {
            if ((s & (1 << end)) == 0)
                continue;
 
            int prev = s - (1 << end);
            for (int j : adjList[end])
            {
                if ((s & (1 << j)))
                {
                    dp[s][end] += dp[prev][j];
                    dp[s][end] %= MODVAL;
                }
            }
        }
    }
 
    cout << dp[(1 << n) - 1][n - 1] << endl;
}