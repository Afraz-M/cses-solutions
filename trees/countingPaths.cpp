#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<int>> ancestor;
vector<vector<int>> adj;
vector<int> depth;
int n;
int m;

vector<int> theArr;
vector<int> ans;

void thedfs(int root, int parent)
{
    ans[root] = theArr[root];
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;
        thedfs(child, root);
        ans[root] += ans[child];
    }
}

int dest(int src, int val)
{
    for (int i = 0; i < 20; i++)
    {
        if (val & (1 << i))
            src = ancestor[src][i];
    }
    return src;
}

void adfs(int root, int parent)
{
    ancestor[root][0] = parent;
    depth[root] = depth[parent] + 1;
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;
        adfs(child, root);
    }
}

int lca(int a, int b)
{
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
        return b;
    }

    for (int i = 18; i >= 0; i--)
    {
        if (ancestor[a][i] != ancestor[b][i])
        {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }

    return ancestor[a][0];
}

int main(void)
{
    iostream::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    ancestor = vector<vector<int>>(n + 1, vector<int>(20, 0));
    adj = vector<vector<int>>(n + 1, vector<int>());
    depth = vector<int>(n + 1, -1);
    theArr = vector<int>(n + 1, 0);
    ans = vector<int>(n + 1, 0);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    adfs(1, 0);

    for (int j = 1; j < 19; j++)
    {
        for (int i = 2; i <= n; i++)
        {
            ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
        }
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        theArr[a] += 1;
        theArr[b] += 1;
        theArr[lca(a, b)] -= 1;
        theArr[ancestor[lca(a, b)][0]] -= 1;
    }

    thedfs(1, 0);
    ans.erase(ans.begin());
    for (auto val : ans)
        cout << val << " ";
    cout << endl;
}