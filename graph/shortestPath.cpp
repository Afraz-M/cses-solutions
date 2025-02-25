#include <bits/stdc++.h>
 
using namespace std;
 
long long N, M;
map<long long, map<long long, long long>> adjList;
vector<long long> dist;
 
int main()
{
    cin >> N >> M;
    dist = vector<long long>(N + 1, LLONG_MAX);
    dist[1] = 0;
 
    for (long long i = 0; i < M; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        if (adjList.count(a) == 0)
            adjList[a] = map<long long, long long>();
        if (adjList[a].count(b) == 0)
            adjList[a][b] = c;
        adjList[a][b] = min(adjList[a][b], c);
    }
 
    // for (auto kv : adjList)
    // {
    //     cout << get<0>(kv) << endl;
    //     for (auto kv2 : get<1>(kv))
    //     {
    //         cout << "\t" << get<0>(kv2) << " " << get<1>(kv2) << endl;
    //     }
    // }
 
    set<long long> sptSet;
    priority_queue<tuple<long long, long long>, vector<tuple<long long, long long>>, greater<tuple<long long, long long>>> pq;
    pq.push(make_tuple(0, 1));
 
    while (!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();
 
        while (sptSet.count(get<1>(curr)) == 1 && !pq.empty())
        {
            curr = pq.top();
            pq.pop();
        }
 
        sptSet.insert(get<1>(curr));
        for (auto kv : adjList[get<1>(curr)])
        {
            long long dest = get<0>(kv), d = get<1>(kv);
            if (sptSet.count(dest) == 1)
                continue;
            if (get<0>(curr) + d < dist[dest])
            {
                dist[dest] = get<0>(curr) + d;
                pq.push(make_tuple(dist[dest], dest));
            }
        }
    }
 
    dist.erase(dist.begin());
    for (auto c : dist)
        cout << c << " ";
    cout << endl;
}