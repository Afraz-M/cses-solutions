#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<set<int>> colors;
vector<int> ans;

void dfs(int root, int parent)
{
    for (auto child : adj[root])
    {
        if (parent == child)
            continue;
        dfs(child, root);
        if (colors[root].size() < colors[child].size())
        {
            swap(colors[root], colors[child]);
        }
        for (int item : colors[child])
            colors[root].insert(item);
    }
    ans[root] = colors[root].size();
}

int main()
{
    int n;
    cin >> n;

    adj = vector<vector<int>>(n + 1, vector<int>());
    colors = vector<set<int>>(n + 1, set<int>());
    ans = vector<int>(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        colors[i].insert(tmp);
    }

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    ans.erase(ans.begin());
    for (auto val : ans)
        cout << val << " ";
    cout << endl;
}