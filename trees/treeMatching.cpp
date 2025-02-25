#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
vector<vector<int>> children;
vector<vector<int>> table;

void dfs(int root, int parent)
{
    for (int child : children[root])
    {
        if (child == parent)
            continue;
        dfs(child, root);
        table[2][root] += max(table[2][child], table[1][child]);
    }

    for (int child : children[root])
    {
        if (child == parent)
            continue;
        table[1][root] = max(table[1][root], table[2][child] + 1 + table[2][root] - max(table[1][child], table[2][child]));
    }
}

int main(void)
{
    cin >> n;
    children = vector<vector<int>>(n + 1, vector<int>());
    table = vector<vector<int>>(3, vector<int>(n + 1, 0));

    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        children[a].push_back(b);
        children[b].push_back(a);
    }

    dfs(1, 0);
    cout << max(table[1][1], table[2][1]) << endl;
}