#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges;

class DSU
{
public:
    int *parent;
    int *rank;

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
                rank[s2] += rank[s1];
            }
            else if (rank[s1] > rank[s2])
            {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += rank[s2];
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
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    DSU dsu = DSU(n + 1);
    int count = n;
    int largest = 1;

    for (auto edge : edges)
    {
        int a = edge[0], b = edge[1];
        if (dsu.find(a) != dsu.find(b))
            count -= 1;
        dsu.unite(a, b);
        largest = max(largest, dsu.rank[dsu.find(a)]);
        largest = max(largest, dsu.rank[dsu.find(b)]);
        cout << count << " " << largest << " " << endl;
    }
}