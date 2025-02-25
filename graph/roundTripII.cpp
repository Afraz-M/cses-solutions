#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjList;
int N, M;

set<int> black, white, grey;
map<int, int> par;
int startnode = -1;
int parnode = -1;

bool dfs(int i)
{
    white.erase(i);
    grey.insert(i);

    for (auto nei : adjList[i])
    {
        if (black.count(nei) == 1)
            continue;
        if (grey.count(nei) == 1)
        {
            startnode = nei;
            parnode = i;
            return true;
        }
        par[nei] = i;
        if (dfs(nei))
            return true;
    }

    grey.erase(i);
    black.insert(i);
    return false;
}

int main(void)
{
    cin >> N >> M;
    adjList = vector<vector<int>>(N + 1, vector<int>());

    for (int i = 1; i <= N; i++)
        white.insert(i);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    par[1] = -1;
    for (int i = 1; i <= N; i++)
    {
        if (white.count(i) == 0)
            continue;
        if (dfs(i))
            break;
    }

    // for (auto kv : par)
    // {
    //     cout << kv.first << " " << kv.second << " " << endl;
    // }

    if (startnode == -1)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> final;
    final.push_back(startnode);
    int curr = parnode;
    while (curr != startnode)
    {
        final.push_back(curr);
        curr = par[curr];
    }
    final.push_back(startnode);

    reverse(final.begin(), final.end());
    cout << final.size() << endl;
    for (auto v : final)
        cout << v << " ";
    cout << endl;
}