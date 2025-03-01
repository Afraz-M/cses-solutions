#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<int>> ancestor;
vector<int> depth;
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

int dfs(int root)
{
    if (depth[root] != -1)
        return depth[root];
    depth[root] = 1 + dfs(ancestor[root][0]);
    return depth[root];
}

int main(void)
{
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    ancestor = vector<vector<int>>(n + 1, vector<int>(20, 0));
    depth = vector<int>(n + 1, -1);
    depth[1] = 0;

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

    for (int i = 1; i <= n; i++)
    {
        dfs(i);
    }

    // for (auto d : depth)
    //     cout << d << " ";
    // cout << endl;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        if (depth[a] > depth[b])
        {
            a = dest(a, depth[a] - depth[b]);
        }
        else if (depth[b] > depth[a])
        {
            b = dest(b, depth[b] - depth[a]);
        }

        if (a == b)
        {
            cout << b << endl;
            continue;
        }

        for (int i = 18; i >= 0; i--)
        {
            if (ancestor[a][i] != ancestor[b][i])
            {
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        }

        cout << ancestor[a][0] << endl;

        // int lo = 0;
        // int hi = 200000;
        // int cand = -1;
        // while (lo <= hi)
        // {
        //     int mid = (lo + hi) / 2;
        //     if (dest(a, mid) == dest(b, mid))
        //     {
        //         cand = mid;
        //         hi = mid - 1;
        //     }
        //     else
        //     {
        //         lo = mid + 1;
        //     }
        // }
        // cout << dest(a, cand) << endl;
    }
}