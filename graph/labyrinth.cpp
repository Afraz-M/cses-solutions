#include <bits/stdc++.h>

using namespace std;

char grid[1002][1002] = {'#'};
bool visited[1002][1002] = {0};
int N, M;
queue<tuple<int, int>> q;
vector<char> path;
map<tuple<int, int>, char> parents;

void backtrack(int i, int j)
{
    char dir = parents[make_tuple(i, j)];
    if (dir == 'O')
        return;
    // cout << i << ", " << j << ", " << dir << endl;
    if (dir == 'L')
    {
        path.push_back('R');
        backtrack(i, j - 1);
    }
    else if (dir == 'R')
    {
        path.push_back('L');
        backtrack(i, j + 1);
    }
    else if (dir == 'U')
    {
        path.push_back('D');
        backtrack(i - 1, j);
    }
    else if (dir == 'D')
    {
        path.push_back('U');
        backtrack(i + 1, j);
    }
}

bool isValid(int i, int j)
{
    if (i < 0 || i >= N)
        return false;
    if (j < 0 || j >= M)
        return false;
    if (grid[i][j] == '#')
        return false;
    if (visited[i][j])
        return false;
    return true;
}

int main()
{
    cin >> N >> M;
    int i, j;
    tuple<int, int> dest;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'A')
            {
                q.push(make_tuple(i, j));
                parents[make_tuple(i, j)] = 'O';
                visited[i][j] = true;
            }
            if (grid[i][j] == 'B')
            {
                dest = make_tuple(i, j);
            }
        }
    }

    bool foundPath = false;

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();
        int x, y;
        tie(x, y) = node;
        if (grid[x][y] == 'B')
        {
            foundPath = true;
            break;
        }
        if (isValid(x - 1, y))
        {
            parents[make_tuple(x - 1, y)] = 'D';
            visited[x - 1][y] = true;
            q.push(make_tuple(x - 1, y));
        }
        if (isValid(x + 1, y))
        {
            parents[make_tuple(x + 1, y)] = 'U';
            visited[x + 1][y] = true;
            q.push(make_tuple(x + 1, y));
        }
        if (isValid(x, y + 1))
        {
            parents[make_tuple(x, y + 1)] = 'L';
            visited[x][y + 1] = true;
            q.push(make_tuple(x, y + 1));
        }
        if (isValid(x, y - 1))
        {
            parents[make_tuple(x, y - 1)] = 'R';
            visited[x][y - 1] = true;
            q.push(make_tuple(x, y - 1));
        }
    }

    if (!foundPath)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << endl;


    backtrack(get<0>(dest), get<1>(dest));

    cout << path.size() << endl;

    int times = path.size();
    for (int i = 0; i < times; i++)
    {
        cout << path.back();
        path.pop_back();
    }
}