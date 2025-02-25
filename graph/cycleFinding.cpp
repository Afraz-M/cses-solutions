#include <bits/stdc++.h>
 
using namespace std;
 
long long N, M;
vector<tuple<long long, long long, long long>> edgeList;
vector<long long> dist;
 
int main()
{
 
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        edgeList.push_back(make_tuple(a, b, c));
    }
 
    dist = vector<long long>(N + 1, 0);
    dist[1] = 0;
 
    for (int i = 0; i < N - 1; i++)
    {
        for (auto edge : edgeList)
        {
            long long a = get<0>(edge), b = get<1>(edge), c = get<2>(edge);
            if (dist[a] + c < dist[b] && dist[a] != LLONG_MAX)
            {
                dist[b] = c + dist[a];
            }
        }
    }
 
    bool flag = false;
    vector<long long> par(N + 1, -1);
 
    for (int i = 0; i < N; i++)
    {
        for (auto edge : edgeList)
        {
            long long a = get<0>(edge), b = get<1>(edge), c = get<2>(edge);
            long long initval = dist[b];
            dist[b] = min(dist[b], dist[a] + c);
            if (dist[b] == initval)
                continue;
            flag = true;
            par[b] = a;
        }
    }
 
    if (!flag)
    {
        cout << "NO" << endl;
        return 0;
    }
 
    // for (auto p : par)
    //     cout << p << " ";
    // cout << endl;
 
    long long startnode = -1;
    for (int i = 0; i < par.size(); i++)
    {
        if (par[i] != -1)
        {
            startnode = i;
            break;
        }
    }
 
    // for (auto p : par)
    //     cout << p << " ";
    // cout << endl;
 
    vector<long long> soln;
    set<long long> st;
    soln.push_back(startnode);
    st.insert(startnode);
    auto curr = par[startnode];
    while (st.count(curr) == 0)
    {
        soln.push_back(curr);
        st.insert(curr);
        curr = par[curr];
    }
    soln.push_back(curr);
 
    cout << "YES" << endl;
    reverse(soln.begin(), soln.end());
    cout << soln[0] << " ";
    for (int i = 1; i < soln.size(); i++)
    {
        cout << soln[i] << " ";
        if (soln[i] == soln[0])
            break;
    }
    cout << endl;
}