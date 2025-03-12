#include <bits/stdc++.h>
 
using namespace std;
 
const int D = 19;
const int MAX_N = 2e5 + 5;
int n, q;
 
vector<int> adj[MAX_N];
int p[MAX_N][D];
int sz[MAX_N];
int depth[MAX_N];
int st[1 << D];
int id[MAX_N];
int top[MAX_N];
int vals[MAX_N];
 
// vector<vector<int>> adj, p;
// vector<int> vals, sz, depth, id, top, st;
 
void update(int idx, int val)
{
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2)
        st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}
 
int query(int lo, int hi)
{
    int ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2)
    {
        if (lo & 1)
            ra = max(ra, st[lo++]);
        if (hi & 1)
            rb = max(rb, st[--hi]);
    }
    return max(ra, rb);
}
 
int dfs_sz(int cur, int par)
{
    sz[cur] = 1;
    p[cur][0] = par;
    for (int chi : adj[cur])
    {
        if (chi == par)
            continue;
        depth[chi] = depth[cur] + 1;
        p[chi][0] = cur;
        sz[cur] += dfs_sz(chi, cur);
    }
    return sz[cur];
}
 
void init_lca()
{
    for (int d = 1; d < 18; d++)
    {
        for (int i = 1; i <= n; i++)
            p[i][d] = p[p[i][d - 1]][d - 1];
    }
}
 
int idx = 1;
void hld(int cur, int par, int tp)
{
    id[cur] = idx++;
    top[cur] = tp;
    update(id[cur], vals[cur]);
    int heavy = -1, heavy_sz = -1;
    for (auto chi : adj[cur])
    {
        if (chi == par)
            continue;
        if (sz[chi] > heavy_sz)
        {
            heavy = chi;
            heavy_sz = sz[chi];
        }
    }
    if (heavy == -1)
        return;
    hld(heavy, cur, tp);
    for (auto chi : adj[cur])
    {
        if (chi == par || chi == heavy)
            continue;
        hld(chi, cur, chi);
    }
}
 
int lca(int a, int b)
{
    if (depth[a] < depth[b])
    {
        swap(a, b);
    }
    for (int d = D - 1; d >= 0; d--)
    {
        if (depth[a] - (1 << d) >= depth[b])
        {
            a = p[a][d];
        }
    }
    for (int d = D - 1; d >= 0; d--)
    {
        if (p[a][d] != p[b][d])
        {
            a = p[a][d];
            b = p[b][d];
        }
    }
    if (a != b)
    {
        a = p[a][0];
        b = p[b][0];
    }
    return a;
}
 
int path(int x, int y)
{
    int ret = 0;
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
            swap(x, y);
        ret = max(ret, query(id[top[x]], id[x]));
        x = p[top[x]][0];
    }
    if (depth[x] > depth[y])
        swap(x, y);
    ret = max(ret, query(id[x], id[y]));
    return ret;
}
 
int main()
{
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    // vals = vector<int>(n + 1, 0);
    // sz = vector<int>(n + 1, 1);
    // depth = vector<int>(n + 1, 0);
    // id = vector<int>(n + 1, 0);
    // top = vector<int>(n + 1, 0);
    // adj = vector<vector<int>>(n + 1, vector<int>());
    // st = vector<int>(4 * n + 1, 0);
    // p = vector<vector<int>>(n + 1, vector<int>(19, 0));
    memset(st, 0, sizeof st);
    for (int i = 1; i <= n; i++)
        cin >> vals[i];
    for (int i = 1; i < n; i++)
    {
        int a = 0, b = 0;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs_sz(1, 0);
    // init_lca();
    hld(1, 1, 1);
    while (q--)
    {
        int t = 0;
        cin >> t;
        if (t == 1)
        {
            int s, x;
            cin >> s >> x;
            vals[s] = x;
            update(id[s], x);
        }
        else
        {
            int a = 0, b = 0;
            cin >> a >> b;
            cout << path(a, b) << " ";
        }
    }
}