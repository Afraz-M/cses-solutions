#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<tuple<long long, long long, long long>> edges;
vector<long long> distarr;
set<long long> markednodes;
vector<set<int>> adjList;
vector<bool> visited;

void dfs(int i)
{
    if (visited[i])
        return;

    visited[i] = true;
    for (int node : adjList[i])
    {
        dfs(node);
    }
}

int main()
{
    cin >> N >> M;
    distarr = vector<long long>(N + 1, LLONG_MAX);
    distarr[1] = 0;

    for (int i = 0; i < M; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        edges.push_back(make_tuple(a, b, -c));
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (auto edge : edges)
        {
            long long a = get<0>(edge), b = get<1>(edge), c = get<2>(edge);
            if (distarr[a] + c < distarr[b] && distarr[a] != LLONG_MAX)
            {
                distarr[b] = distarr[a] + c;
            }
        }
    }

    bool negcexists = false;
    long long soln = distarr[N];
    for (auto edge : edges)
    {
        long long a = get<0>(edge), b = get<1>(edge), c = get<2>(edge);
        if (distarr[a] + c < distarr[b] && distarr[a] != LLONG_MAX)
        {
            markednodes.insert(a);
            markednodes.insert(b);
            negcexists = true;
        }
    }

    if (!negcexists)
    {
        cout << -soln << endl;
        return 0;
    }

    adjList = vector<set<int>>(N + 1, set<int>());
    for (auto edge : edges)
    {
        int a = get<0>(edge), b = get<1>(edge);
        adjList[b].insert(a);
    }

    visited = vector<bool>(N + 1, false);
    dfs(N);

    for (auto node : markednodes)
    {
        if (visited[node])
        {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << -soln << endl;
}