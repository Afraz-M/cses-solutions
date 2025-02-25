#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> path;
vector<bool> vis;

void dfs(int node){
    while(!g[node].empty()){
        int v = g[node].back().first; 
        int edge = g[node].back().second;
        g[node].pop_back();
        if(vis[edge]) continue;
        vis[edge] = true;
        dfs(v);
    }
    path.push_back(node);
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> degree(n, 0);
    g.resize(n);
    degree.resize(n);
    vis.resize(m);

    for(int i = 0;i < m; i++){
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].push_back({y, i});
        g[y].push_back({x, i});
        degree[x]++, degree[y]++;
    }

    for(int i = 0; i < n; i++){
        if(degree[i] % 2){
            cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
    }

    dfs(0);

    if(path.size() != m + 1) cout << "IMPOSSIBLE" << '\n';
    else {
        for(auto p : path) cout << p + 1 << ' ';
        cout << endl;
    }
    return 0;
}