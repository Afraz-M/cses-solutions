#include<bits/stdc++.h>

using namespace std;

int n, k;
vector<int> adj[200001];
int sz[200001], processed[200001], cnt[200001]{1};

int dfs(int node, int parent = 0){
    sz[node] = 1;
    for(int chi : adj[node]) {
		if (!processed[chi] && chi != parent) sz[node] += dfs(chi, node);
    }
    return sz[node];
}

int getCentroid(int node, int parent, int size) {
    for(int chi : adj[node]) {
        if (chi == parent) continue;
        if(sz[chi] >= size && !processed[chi] && chi != parent) return getCentroid(chi, node, size);
    }

    return node;
}
long long res = 0;
int maxDepth = 0;
void getCount(int node, int parent, int depth = 1, bool filling = false) {
    if(depth > k) return;
    maxDepth = max(depth, maxDepth); 
    if(filling) cnt[depth]++;
    else res += cnt[k - depth];
    for(int i : adj[node]) {
        if(!processed[i] && i != parent) {
            getCount(i, node, depth + 1, filling);
        }
    }
}

void centroidDecomposition(int node){
    int size = dfs(node) >> 1;
    int centroid = getCentroid(node, 0, size);
    processed[centroid] = 1;
    maxDepth = 0;
    for(int i : adj[centroid]) {
        if(!processed[i]) {
            getCount(i, centroid, 1, false);
            getCount(i, centroid, 1, true);

        }
    }
    fill(cnt + 1, cnt + maxDepth + 1, 0);
	for (int i : adj[centroid])
		if (!processed[i]) centroidDecomposition(i);
}

int main(){
    iostream::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for(int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    centroidDecomposition(1);
    // dfs(1);
    cout << res;
    return 0;
}
