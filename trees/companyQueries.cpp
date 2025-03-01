#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<int>> ancestor;
int n;
int m;

int dest(int src, int val)
{
    for (int i = 0; i < 20; i++)
    {
        if (val & (1 << i))
            src = ancestor[src][i];
    }
    return src;
}

int main(void)
{
    cin >> n >> m;
    ancestor = vector<vector<int>>(n + 1, vector<int>(20, 0));
    for (int i = 2; i <= n; i++)
    {
        cin >> ancestor[i][0];
    }

    for (int j = 1; j < 19; j++)
    {
        for (int i = 2; i <= n; i++)
        {
            ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
        }
    }

    for (int i = 0; i < m; i++)
    {
        int src, val;
        cin >> src >> val;
        int ans = dest(src, val);
        if (ans == 0)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }
}