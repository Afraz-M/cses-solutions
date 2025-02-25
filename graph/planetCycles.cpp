#include <bits/stdc++.h>

using namespace std;

bool visited[200000] = {false};
vector<int> pathLen(200000, 0);
vector<int> dest(200000, 0);
queue<int> path;
int steps = 0;

void dfs(int planet){
    path.push(planet);
    if(visited[planet]){
        steps += pathLen[planet];
        return;
    }
    visited[planet] = true;
    steps++;
    dfs(dest[planet]);
}


int main(){
    int n;
    cin >> n;
    for(int i = 0;i < n; i++){
        cin >> dest[i];
        dest[i]--;
    }
    for(int i = 0;i < n; i++){
        if(!visited[i]) {
            steps = 0;
            dfs(i);
            int decrement = 1;
            while(!path.empty()){
                if(path.front() == path.back()) decrement = 0;
                pathLen[path.front()] = steps;
                path.pop();
                steps -= decrement;
            }
        }
    }
    for(int i = 0; i< n; i++) cout << pathLen[i] << " ";
    cout << endl;
    return 0; 
}