#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
int res = 0;

int dfs(int root, int p){
    priority_queue<int> leaves;
    for(auto nei : adj[root]){
        if(nei == p) continue;
        leaves.push(dfs(nei, root));
    }
    if(leaves.size() < 2) {
        if(leaves.size() == 0){
            return 0;
        }
        res = max(res, 1 + leaves.top());
        return 1 + leaves.top();
    } else {
        int leaf = leaves.top();
        leaves.pop();
        int leaf2 = leaves.top();
        res = max(res, leaf + leaf2 + 2);
        return max(leaf, leaf2) + 1;
    }
}

int main(){
    int n;
    cin >> n;
    adj = vector<vector<int>>(n + 1, vector<int>());
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1);
    cout << res << endl;
}