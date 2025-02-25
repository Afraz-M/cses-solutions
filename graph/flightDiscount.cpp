#include <bits/stdc++.h>
 
using namespace std;
 
long long N, M;
map<long long, map<long long, long long>> adjList;
map<long long, map<long long, long long>> adjListn;
vector<long long> dist1;
vector<long long> distn;
vector<tuple<long long, long long, long long>> edgeList;
 
int main()
{
 
    std::cout << std::setiosflags(std::ios_base::fixed) << std::setprecision(0);
 
    cin >> N >> M;
    dist1 = vector<long long>(N + 1, LLONG_MAX);
    dist1[1] = 0;
    distn = vector<long long>(N + 1, LLONG_MAX);
    distn[N] = 0;
 
    for (long long i = 0; i < M; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        edgeList.push_back(make_tuple(a, b, c));
        if (adjList.count(a) == 0)
            adjList[a] = map<long long, long long>();
        if (adjList[a].count(b) == 0)
            adjList[a][b] = c;
        adjList[a][b] = min(adjList[a][b], c);
 
        if (adjListn.count(b) == 0)
            adjListn[b] = map<long long, long long>();
        if (adjListn[b].count(a) == 0)
            adjListn[b][a] = c;
        adjListn[b][a] = min(adjListn[b][a], c);
    }
 
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
            long long dest = get<0>(kv), dist = get<1>(kv);
            if (sptSet.count(dest) == 1)
                continue;
            if (get<0>(curr) + dist < dist1[dest])
            {
                dist1[dest] = get<0>(curr) + dist;
                pq.push(make_tuple(dist1[dest], dest));
            }
        }
    }
 
    // for (auto c : dist1)
    //     cout << c << " ";
    // cout << endl;
 
    sptSet = set<long long>();
    pq.push(make_tuple(0, N));
 
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
        for (auto kv : adjListn[get<1>(curr)])
        {
            long long dest = get<0>(kv), dist = get<1>(kv);
            if (sptSet.count(dest) == 1)
                continue;
            if (get<0>(curr) + dist < distn[dest])
            {
                distn[dest] = get<0>(curr) + dist;
                pq.push(make_tuple(distn[dest], dest));
            }
        }
    }
 
    // for (auto c : distn)
    //     cout << c << " ";
    // cout << endl;
 
    long double mincost = LLONG_MAX;
    for (auto edge : edgeList)
    {
        long long a = get<0>(edge), b = get<1>(edge), c = get<2>(edge);
        if (dist1[a] == LLONG_MAX || distn[b] == LLONG_MAX)
            continue;
        long double thiscost = dist1[a] + distn[b] + c / 2;
        mincost = min(thiscost, mincost);
    }
 
    cout << mincost << endl;
}