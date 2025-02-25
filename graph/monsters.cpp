#include <bits/stdc++.h>

using namespace std;

char grid[1000][1000];
queue<tuple<int, int>> q;
int monstdist[1000][1000];
int N, M;
vector<char> path;
vector<vector<bool>> visited(1000, vector<bool>(1000, false));

bool isvalid(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M && grid[i][j] != '#';
}

bool dfs(int i, int j, int steps)
{
    if (!isvalid(i, j) || monstdist[i][j] <= steps || visited[i][j])
        return false;

    if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
        return true;

    visited[i][j] = true;

    path.push_back('L');
    if (dfs(i, j - 1, steps + 1))
        return true;
    path.pop_back();

    path.push_back('R');
    if (dfs(i, j + 1, steps + 1))
        return true;
    path.pop_back();

    path.push_back('D');
    if (dfs(i + 1, j, steps + 1))
        return true;
    path.pop_back();

    path.push_back('U');
    if (dfs(i - 1, j, steps + 1))
        return true;
    path.pop_back();

    visited[i][j] = false;

    return false;
}

int main()
{
    cin >> N >> M;
    int srcx, srcy;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            monstdist[i][j] = INT_MAX;
            cin >> grid[i][j];
            if (grid[i][j] == 'M')
            {
                q.push(make_tuple(i, j));
                monstdist[i][j] = 0;
            }
            if (grid[i][j] == 'A')
            {
                srcx = i;
                srcy = j;
            }
        }
    }

    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();
        int x = get<0>(curr), y = get<1>(curr);
        int currdist = monstdist[x][y];

        if (isvalid(x + 1, y) && monstdist[x + 1][y] == INT_MAX)
        {
            monstdist[x + 1][y] = currdist + 1;
            q.push(make_tuple(x + 1, y));
        }

        if (isvalid(x, y + 1) && monstdist[x][y + 1] == INT_MAX)
        {
            monstdist[x][y + 1] = currdist + 1;
            q.push(make_tuple(x, y + 1));
        }

        if (isvalid(x - 1, y) && monstdist[x - 1][y] == INT_MAX)
        {
            monstdist[x - 1][y] = currdist + 1;
            q.push(make_tuple(x - 1, y));
        }

        if (isvalid(x, y - 1) && monstdist[x][y - 1] == INT_MAX)
        {
            monstdist[x][y - 1] = currdist + 1;
            q.push(make_tuple(x, y - 1));
        }
    }

    if (!dfs(srcx, srcy, 0))
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    cout << path.size() << endl;
    for (auto c : path)
    {
        cout << c;
    }
    cout << endl;
}