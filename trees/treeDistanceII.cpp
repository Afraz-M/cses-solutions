#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<int>> adj;
vector<int> sz;
vector<ll> ans;
int n;

void dfs1(int root, int parent, int depth)
{
    ans[1] += depth;
    sz[root] = 1;
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;
        dfs1(child, root, depth + 1);
        sz[root] += sz[child];
    }
}

void dfs2(int root, int parent)
{
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;
        ans[child] += ans[root] + n - 2 * sz[child];
        dfs2(child, root);
    }
}

int main(void)
{
    cin >> n;
    adj = vector<vector<int>>(n + 1, vector<int>());
    sz = vector<int>(n + 1, 0);
    ans = vector<ll>(n + 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0);

    ans.erase(ans.begin());
    for (auto val : ans)
        cout << val << " ";
    cout << endl;
}