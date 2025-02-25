#include<bits/stdc++.h>

using namespace std;

int main(){
    long long n, m, k;
    cin >> n >> m >> k;
    map <long long, vector<tuple<long, long>>> adjList;
    vector<long long> dist (n + 1, LLONG_MAX);
    vector<vector<long long>> res(n + 1, vector<long long> (k + 1, LLONG_MAX));
    priority_queue<tuple<long long, long long>, vector<tuple<long long, long long>>, greater<tuple<long long, long long>>> pq;
    dist[1] = 0;
    for(int i = 0; i < m; i++){
        long long a, b, c;
        cin >> a >> b >> c;
        adjList[a].push_back(make_tuple(b, c));
    }
    pq.push(make_tuple(0, 1));
    while(!pq.empty()){
        long long v, d;
        tie(d, v) = pq.top();
        pq.pop();

        if (res[v][k - 1] > d){
            res[v][k] = d;
            sort(res[v].begin(), res[v].end());
        
        for(auto node : adjList[v]){
            long long dist, u;
            tie(u, dist) = node;
            if(d + dist < res[u][k - 1]) {
            pq.push(make_tuple(d + dist, u));
            }
        }
        }
    }
    for(int i = 0; i < k; i++){
        cout << res[n][i] << endl;
    }
    return 0;
}