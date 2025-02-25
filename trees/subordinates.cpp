#include <bits/stdc++.h>

using namespace std;
map<int, vector<int>> tree;
vector<int> ans;

int dfs(int i){
    if(tree.count(i) == 0) {
        ans[i] = 0;
        return 1;
    }
    int sum = 0;
    for(auto nei : tree[i]) {
        sum += dfs(nei);
    }
    ans[i] = sum;
    return ans[i] + 1;
}

int main(){
    int n;
    cin >> n;
    ans = vector<int>(n + 1, -1);
    for(int i = 2; i < n + 1; i++){
        int x;
        cin >> x;
        if(!tree.count(x)) tree[x] = vector<int>();
        tree[x].push_back(i);
    }
    dfs(1);
    ans.erase(ans.begin());
    for(auto i : ans) {
        cout << i << " ";
    }
    return 0;
}