#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> radj;
vector<bool> visited;
priority_queue<pair<int, int>> pq;
int mytime = 0;
vector<int> nodeToSCC;
vector<vector<int>> sccToNode;
vector<pair<int, int>> edges;
vector<set<int>> sccadj;
set<int> soln;

int neg(int a)
{
    if (a > m)
        return a - m;
    return a + m;
}

void assign(int a)
{
    if (soln.count(a) == 1 || soln.count(neg(a)) == 1)
        return;
    soln.insert(a);
}

void krdfs1(int root)
{
    if (visited[root])
        return;

    mytime += 1;
    visited[root] = true;

    for (auto nei : adj[root])
    {
        krdfs1(nei);
    }

    mytime += 1;
    pq.push(make_pair(mytime, root));
}

void krdfs2(int root, int sccid)
{
    if (visited[root])
        return;

    visited[root] = true;
    nodeToSCC[root] = sccid;
    for (auto nei : radj[root])
    {
        krdfs2(nei, sccid);
    }
}

void topodfs(int root)
{
    if (visited[root])
        return;

    visited[root] = true;
    for (auto nei : sccadj[root])
    {
        topodfs(nei);
    }

    for (auto node : sccToNode[root])
    {
        assign(node);
    }
}

int main(void)
{
    cin >> n >> m;
    adj = vector<vector<int>>(2 * m + 2, vector<int>());
    radj = vector<vector<int>>(2 * m + 2, vector<int>());
    visited = vector<bool>(2 * m + 1, false);
    nodeToSCC = vector<int>(2 * m + 1, 0);

    for (int i = 0; i < n; i++)
    {
        char first, second;
        int a, b;
        cin >> first >> a >> second >> b;
        if (first == '-')
            a = neg(a);
        if (second == '-')
            b = neg(b);

        edges.push_back(make_pair(neg(a), b));
        edges.push_back(make_pair(neg(b), a));

        adj[neg(a)].push_back(b);
        radj[b].push_back(neg(a));
        adj[neg(b)].push_back(a);
        radj[a].push_back(neg(b));
    }

    // for (int i = 1; i <= 2 * m; i++)
    // {
    //     cout << i << ": ";
    //     for (auto j : adj[i])
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 1; i <= 2 * m; i++)
    {
        krdfs1(i);
    }

    visited = vector<bool>(2 * m + 1, false);
    int sccid = 1;
    while (!pq.empty())
    {
        int root = pq.top().second;
        pq.pop();
        if (!visited[root])
        {
            krdfs2(root, sccid);
            sccid += 1;
        }
    }

    for (int ai = 1; ai <= m; ai++)
    {
        int negai = neg(ai);
        if (nodeToSCC[negai] == nodeToSCC[ai])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    sccToNode = vector<vector<int>>(sccid, vector<int>());
    for (int i = 1; i <= 2 * m; i++)
        sccToNode[nodeToSCC[i]].push_back(i);

    // for (int i = 1; i < sccid; i++)
    // {
    //     cout << i << ": ";
    //     for (auto v : sccToNode[i])
    //     {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    sccadj = vector<set<int>>(sccid, set<int>());
    for (auto edge : edges)
    {
        int a = edge.first, b = edge.second;
        int scca = nodeToSCC[a];
        int sccb = nodeToSCC[b];
        if (scca == sccb)
            continue;
        sccadj[scca].insert(sccb);
    }

    // for (int i = 1; i < sccid; i++)
    // {
    //     cout << i << ": ";
    //     for (auto v : sccadj[i])
    //     {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    visited = vector<bool>(sccid, false);
    for (int i = 1; i < sccid; i++)
    {
        topodfs(i);
    }

    for (int i = 1; i <= m; i++)
    {
        if (soln.count(i) == 1)
            cout << "+ ";
        else
            cout << "- ";
    }
    cout << endl;
}