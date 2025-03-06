#include <bits/stdc++.h>


using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> val, sz, p, depth;

int dfs(int root, int parent) {
    p[root] = parent;
    for(int chi : adj[cur]) {
        if(chi == par) continue;
        depth[chi] = depth[root] + 1;
        p[chi] = root;
        sz[root] += dfs(chi, root);
    }
    return sz[root];
}

int main(){
    cin >> n >> q;
    adj = vector<vector<int>>(n + 1, vector<int>());
    sz = vector<int>(n + 1, 1);
    sz = vector<int>(n + 1, 0);
    depth = vector<int>(n + 1, 0);
    for(int i = 0; i <= n; i++) cin >> val[i];
    for(int i = 0; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}