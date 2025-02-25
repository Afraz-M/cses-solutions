#include <bits/stdc++.h>

using namespace std;

int N, M;
map<int, vector<int>> adjList;
queue<int> q;

int main()
{
    cin >> N >> M;
    vector<int> colors(N + 1, 0);
    vector<bool> visited(N + 1, false);

    for (int i = 0; i < M; i++)
    {
        int src, dest;
        cin >> src >> dest;
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    for (int i = 0; i < N; i++)
    {
        if (visited[i])
            continue;

        q.push(i);
        colors[i] = 1;
        visited[i] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (int nei : adjList[current])
            {
                if (visited[nei] == true)
                {
                    if (colors[nei] == colors[current])
                    {
                        cout << "IMPOSSIBLE" << endl;
                        return 0;
                    }
                    else
                    {
                        continue;
                    }
                }
                colors[nei] = 3 - colors[current];
                visited[nei] = true;
                q.push(nei);
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << colors[i] << " ";
    }
    cout << endl;
}