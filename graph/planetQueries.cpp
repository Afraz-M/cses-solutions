#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
int n, q;
vector<int> t;
vector<vector<int>> table;
 
int dest(int src, int val)
{
    for (int i = 0; i < 30; i++)
    {
        if (val & (1 << i))
            src = table[i][src];
    }
    return src;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n >> q;
 
    table = vector<vector<int>>(30, vector<int>(n + 1, 0));
 
    for (int i = 1; i <= n; i++)
    {
        cin >> table[0][i];
    }
 
    for (int i = 1; i < 30; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            table[i][j] = table[i - 1][table[i - 1][j]];
        }
    }
 
 
    for (int i = 0; i < q; i++)
    {
        int src;
        int val;
        cin >> src >> val;
        cout << dest(src, val) << endl;
    }
}