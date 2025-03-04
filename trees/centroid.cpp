#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
vector<vector<int>> adj;
vector<int> sz;

int dfs(int root, int parent)
{
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;

        sz[root] += dfs(child, root);
    }
    return sz[root];
}

int centroid(int root, int parent)
{
    for (auto child : adj[root])
    {
        if (child == parent)
            continue;

        if (2 * sz[child] > n)
            return centroid(child, root);
    }

    return root;
}

int main(void)
{
    cin >> n;
    adj = vector<vector<int>>(n + 1, vector<int>());
    sz = vector<int>(n + 1, 1);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    cout << centroid(1, 0) << endl;
}