#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> edges;

class DSU
{
    int *parent;
    int *rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
            {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2])
            {
                parent[s2] = s1;
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

int main(void)
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        long long a, b, cost;
        cin >> a >> b >> cost;
        edges.push_back({cost, a, b});
    }
    sort(edges.begin(), edges.end());

    DSU dsu = DSU(n + 1);
    long long res = 0;

    for (auto edge : edges)
    {
        long long cost = edge[0], a = edge[1], b = edge[2];
        if (dsu.find(a) == dsu.find(b))
            continue;
        dsu.unite(a, b);
        res += cost;
    }

    int a = dsu.find(1);
    for (int node = 1; node <= n; node++)
    {
        if (dsu.find(node) != dsu.find(1))
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    cout << res << endl;
}