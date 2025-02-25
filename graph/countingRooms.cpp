#include <bits/stdc++.h>
#include <iostream>

using namespace std;

bool isvalid(int i, int j, int n, int m)
{
    if (i < 0 || i >= n)
        return false;
    if (j < 0 || j >= m)
        return false;

    return true;
}

void dfs(int i, int j, char grid[1000][1000], int n, int m)
{
    if (!isvalid(i, j, n, m))
        return;

    if (grid[i][j] == '#')
        return;

    grid[i][j] = '#';
    dfs(i + 1, j, grid, n, m);
    dfs(i - 1, j, grid, n, m);
    dfs(i, j + 1, grid, n, m);
    dfs(i, j - 1, grid, n, m);
}

int main(void)
{
    int n, m;
    cin >> n >> m;

    char grid[1000][1000];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '#')
                continue;

            dfs(i, j, grid, n, m);
            count += 1;
        }
    }

    cout << count;
}

