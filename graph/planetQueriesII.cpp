#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> next(n);
    vector<vector<int>> before(n);
    for(int i = 0; i < n; i++){
        cin >> next[i];
        next[i]--;
        before[next[i]].push_back(i);
    }
    vector<int> cycle_id(n, -2);
    vector<map<int, int>> cycles;
    for(int i = 0; i < n; i++){
        if(cycle_id[i] != -2) continue;
        vector<int> path{i};
        int at = i;
        while(cycle_id[next[at]] == -2){
            at = next[at];
            cycle_id[at] = -3;
            path.push_back(at);
        }
        map<int, int> cycle;
        bool in_cycle = false;
        for(int p : path){
            in_cycle = in_cycle || p == next[at];
            if(in_cycle) {cycle[p] = cycle.size();}
            cycle_id[p] = in_cycle ? cycles.size() : -1;
        }
        cycles.push_back(cycle);
    }

    vector<int> cyc_dist(n);
    for(int i = 0; i < n; i++){
        if(cycle_id[next[i]] == -1 || cycle_id[i] != -1) { continue; }
        cyc_dist[i] = 1;
        vector<int> stack(before[i]);
        while(!stack.empty()){
            int curr = stack.back();
            stack.pop_back();
            cyc_dist[curr] = cyc_dist[next[curr]] + 1;
            stack.insert(stack.end(), before[curr].begin(), before[curr].end());
        }
    }

    int log2 = ceil(std::log2(n));
    vector<vector<int>> ancestors(n, vector<int>(log2 + 1));
	for (int p = 0; p < n; p++) { ancestors[p][0] = next[p]; }
	for (int i = 1; i <= log2; i++) {
		for (int p = 0; p < n; p++) {
			ancestors[p][i] = ancestors[ancestors[p][i - 1]][i - 1];
		}
	}

    auto advance = [&](int pos, int dist) {
        for(int pow = log2; pow >= 0; pow--){
            if((dist & (1 << pow)) != 0) { pos = ancestors[pos][pow];}
        }
        return pos;
    };

    for(int qu = 0; qu < q; qu++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (cycle_id[ancestors[u][log2]] != cycle_id[ancestors[v][log2]]) {
            cout << -1 << '\n';
            continue;
        }
        if(cycle_id[u] != -1 || cycle_id[v] != -1){
            if(cycle_id[v] == -1 && cycle_id[u] != -1){
                cout << -1 << '\n';
                continue;
            }
            int dist = cyc_dist[u];
            int u_cyc = advance(u, cyc_dist[u]);
            map<int, int> &cyc = cycles[cycle_id[u_cyc]];
            int u_ind = cyc[u_cyc];
            int v_ind = cyc[v];
            int diff = u_ind <= v_ind ? v_ind - u_ind : cyc.size() - (u_ind - v_ind);
            cout << diff + dist << '\n';
        } else {
            if(cyc_dist[v] > cyc_dist[u]) {
                cout << -1 << '\n';
                continue;
            }
            int diff = cyc_dist[u] - cyc_dist[v];
            cout << (advance(u, diff) == v ? diff : -1) << '\n';
        }
    }
}