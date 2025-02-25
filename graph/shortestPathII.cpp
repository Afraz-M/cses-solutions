#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> grid = vector<vector<long long>>(n + 1, vector<long long>(n + 1, LLONG_MAX));

    for (int i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        grid[a][b] = min(c, grid[a][b]);
        grid[b][a] = min(c, grid[b][a]);
    }

    for (int i = 1; i <= n; i++)
    {
        grid[i][i] = 0;
    }

    for (int k = 0; k <= n; k++)
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (grid[i][j] > (grid[i][k] + grid[k][j]) && (grid[k][j] != LLONG_MAX && grid[i][k] != LLONG_MAX))
                    grid[i][j] = grid[i][k] + grid[k][j];
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int src, dest;
        cin >> src >> dest;

        if (grid[src][dest] == LLONG_MAX)
            cout << -1 << endl;
        else
            cout << grid[src][dest] << endl;
    }
}