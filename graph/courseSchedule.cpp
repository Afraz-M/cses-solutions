#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjList;
int N, M;

set<int> black, white, grey;
stack<int> st;

bool dfs(int i)
{
    white.erase(i);
    grey.insert(i);

    for (auto nei : adjList[i])
    {
        if (black.count(nei) == 1)
            continue;
        if (grey.count(nei) == 1)
        {
            return true;
        }
        if (dfs(nei))
            return true;
    }

    grey.erase(i);
    black.insert(i);
    st.push(i);
    return false;
}

int main(void)
{
    cin >> N >> M;
    adjList = vector<vector<int>>(N + 1, vector<int>());

    for (int i = 1; i <= N; i++)
        white.insert(i);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    bool cycleExists = false;
    for (int i = 1; i <= N; i++)
    {
        if (white.count(i) == 0)
            continue;
        if (dfs(i))
        {
            cycleExists = true;
            break;
        }
    }

    if (cycleExists)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}