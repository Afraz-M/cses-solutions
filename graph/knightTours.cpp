#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<pair<int, int>> neiRes;
vector<vector<int>> hboard = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 3, 4, 4, 4, 4, 3, 2},
    {0, 3, 4, 6, 6, 6, 6, 4, 3},
    {0, 4, 6, 8, 8, 8, 8, 6, 4},
    {0, 4, 6, 8, 8, 8, 8, 6, 4},
    {0, 4, 6, 8, 8, 8, 8, 6, 4},
    {0, 4, 6, 8, 8, 8, 8, 6, 4},
    {0, 3, 4, 6, 6, 6, 6, 4, 3},
    {0, 2, 3, 4, 4, 4, 4, 3, 2}};
vector<vector<int>> result = vector<vector<int>>(9, vector<int>(9, 0));

bool isValid(pair<int, int> coord)
{
    return coord.first <= 8 && coord.first >= 1 && coord.second <= 8 && coord.second >= 1;
}

void neigh(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    neiRes = vector<pair<int, int>>();
    if (isValid({x + 2, y + 1}))
        neiRes.push_back({x + 2, y + 1});
    if (isValid({x + 2, y - 1}))
        neiRes.push_back({x + 2, y - 1});
    if (isValid({x + 1, y + 2}))
        neiRes.push_back({x + 1, y + 2});
    if (isValid({x + 1, y - 2}))
        neiRes.push_back({x + 1, y - 2});
    if (isValid({x - 2, y + 1}))
        neiRes.push_back({x - 2, y + 1});
    if (isValid({x - 2, y - 1}))
        neiRes.push_back({x - 2, y - 1});
    if (isValid({x - 1, y + 2}))
        neiRes.push_back({x - 1, y + 2});
    if (isValid({x - 1, y - 2}))
        neiRes.push_back({x - 1, y - 2});
}

bool backtrack(pair<int, int> coord, int stepno)
{
    if (stepno == 65)
        return true;
    int x = coord.first;
    int y = coord.second;
    if (result[x][y] != 0)
        return false;

    result[x][y] = stepno;
    neigh(coord);
    priority_queue<pair<int, pair<int, int>>> pq;

    for (auto nei : neiRes)
    {
        int neix = nei.first;
        int neiy = nei.second;
        hboard[neix][neiy]--;
        pq.push({-hboard[neix][neiy], nei});
    }

    while (!pq.empty())
    {
        auto nei = pq.top().second;
        pq.pop();
        if (backtrack(nei, stepno + 1))
            return true;
    }

    result[x][y] = 0;
    neigh(coord);
    for (auto nei : neiRes)
    {
        hboard[nei.first][nei.second]++;
    }
    return false;
}

int main(void)
{
    int x, y;
    cin >> x >> y;
    backtrack({y, x}, 1);

    result.erase(result.begin());
    for (auto row : result)
    {
        row.erase(row.begin());
        for (auto cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}