#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int D = 19;
const int S = (1 << D);

int n, q;
vector<vector<int>> adj, p;
vector<int> vals, sz, depth, id;
int st[S];

int dfs_sz(int cur, int par) {
    for (int chi : adj[cur]) {
		if (chi == par) continue;
		depth[chi] = depth[cur] + 1;
		p[chi][0] = cur;
		sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}

void init_lca() {
	for (int d = 1; d < 18; d++)
    {	
        for (int i = 1; i <= n; i++) p[i][d] = p[p[i][d - 1]][d - 1];
    }
}

int main(){
    cin >> n >> q;
    vals = vector<int>(n + 1, 0);
    sz = vector<int>(n + 1, 1);
    depth = vector<int>(n + 1, 0);
    id = vector<int>(n + 1, 0);
    adj = vector<vector<int>>(n + 1, vector<int>());
    p = vector<vector<int>>(n + 1, vector<int>(19, 0));
    for (int i = 1; i <= n; i++) cin >> vals[i];
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
	dfs_sz(1, 0);
	init_lca();
}