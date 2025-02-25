#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<int>> adj;
vector<int> res;
int n;

int bfs(int src)
{
    queue<pair<int, int>> q;
    vector<bool> vis(n + 1, false);
    q.push({src, 0});
    pair<int, int> u;

    while (!q.empty())
    {
        u = q.front();
        vis[u.first] = true;
        q.pop();

        for (auto nei : adj[u.first])
        {
            if (!vis[nei])
                q.push({nei, u.second + 1});
        }
    }
    return u.first;
}

void bfs2(int start)
{
    queue<pair<int, int>> q;
    vector<bool> vis(n + 1, false);
    q.push({start, 0});

    while (!q.empty())
    {
        pair<int, int> u = q.front();
        q.pop();
        vis[u.first] = true;

        res[u.first] = max(res[u.first], u.second);

        for (auto nei : adj[u.first])
        {
            if (!vis[nei])
                q.push({nei, u.second + 1});
        }
    }
}

int main(void)
{
    cin >> n;
    adj = vector<vector<int>>(n + 1, vector<int>());
    res = vector<int>(n + 1, 0);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int die1 = bfs(1);
    int die2 = bfs(die1);

    bfs2(die1);
    bfs2(die2);

    res.erase(res.begin());
    for (auto val : res)
        cout << val << " ";
    cout << endl;
}