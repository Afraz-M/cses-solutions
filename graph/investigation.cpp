#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
map<int, vector<pair<ll, int>>> edges;
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
const int MODVAL = int(1e9) + 7;
int main(){
    int n, m;
    cin >> n >> m;
    vector<ll> dist(n + 1, LLONG_MAX);
    vector<ll> nums(n + 1, 0);
    vector<int> minf(n + 1, INT_MAX);
    vector<int> maxf(n + 1, INT_MIN);
    bool vis[n + 1] = {false};
    for(int i = 0; i < m; i ++){
        int s, e, cost;
        cin >> s >> e >> cost;
        edges[s].push_back({cost, e});
    }
    dist[1] = 0;
    nums[1] = 1;
    minf[1] = 0;
    maxf[1] = 0;
    pq.push({0, 1});
    while(!pq.empty()){
        int v = pq.top().second;
        pq.pop();
        if (vis[v]){continue;}
        vis[v] = true;
        for(auto edge : edges[v]){
            ll cost = edge.first;
            int nei = edge.second;
            ll alt = (cost + dist[v]);
            if(alt == dist[nei]){
                nums[nei] = (nums[nei] + nums[v]) % MODVAL;
                minf[nei] = min(minf[nei], minf[v] + 1);
                maxf[nei] = max(maxf[nei], maxf[v] + 1);
            } else if(alt < dist[nei]){
                nums[nei] = nums[v];
                maxf[nei] = maxf[v] + 1;
                minf[nei] = minf[v] + 1;
                dist[nei] = alt;
                pq.push({alt , nei});
            }
        }
    }
	cout << dist[n] << " " << nums[n] % MODVAL << " " << minf[n] << " " << maxf[n];
    return 0;
}