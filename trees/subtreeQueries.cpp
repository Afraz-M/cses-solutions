#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template <typename T>
class SegTree
{
public:
    vector<T> tree;
    int n;
    T defval;
    T (*comp)(T, T);

    SegTree(const vector<T> &arr, T (*comp)(T, T), T defval)
        : comp(comp), defval(defval)
    {
        n = arr.size();
        tree.resize(2 * n, 0);
        for (int i = 0; i < n; ++i)
        {
            tree[n + i] = arr[i];
        }
        for (int i = n - 1; i > 0; --i)
        {
            tree[i] = comp(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void printTree()
    {
        for (T val : tree)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    T rq(int a, int b)
    {
        a += n;
        b += n;

        T s = defval;

        while (a < b)
        {
            if (a & 1)
            {
                s = comp(s, tree[a]);
                a++;
            }
            if (b & 1)
            {
                b--;
                s = comp(s, tree[b]);
            }
            a >>= 1;
            b >>= 1;
        }

        return s;
    }

    void uq(int k, T x)
    {
        k += n;
        tree[k] = x;

        for (k /= 2; k >= 1; k /= 2)
        {
            tree[k] = comp(tree[2 * k], tree[2 * k + 1]);
        }
    }
};

template <typename T>
T sumFunc(T a, T b)
{
    return a + b;
}

int n, q;
vector<ll> vals;
vector<vector<int>> adj;

vector<int> ttanodeid;
vector<int> ttasize;
vector<ll> ttaval;

map<int, int> ttaidx;

int dfs(int root, int parent)
{
    ttanodeid.push_back(root);
    ttaval.push_back(vals[root]);

    int idx = ttasize.size();
    ttasize.push_back(1);
    for (auto children : adj[root])
    {
        if (children == parent)
            continue;

        ttasize[idx] += dfs(children, root);
    }

    return ttasize[idx];
}

int main(void)
{
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    adj = vector<vector<int>>(n + 1, vector<int>());
    vals = vector<ll>(n + 1, 0);

    for (int i = 1; i <= n; i++)
        cin >> vals[i];

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    SegTree<ll> st(ttaval, sumFunc<ll>, 0);

    for (int i = 0; i < n; i++)
    {
        ttaidx[ttanodeid[i]] = i;
    }

    for (int i = 0; i < q; i++)
    {
        int qrytype;
        cin >> qrytype;
        if (qrytype == 2)
        {
            int root;
            cin >> root;
            cout << st.rq(ttaidx[root], ttaidx[root] + ttasize[ttaidx[root]]) << endl;
        }
        else
        {
            int root;
            ll val;
            cin >> root >> val;
            st.uq(ttaidx[root], val);
        }
    }
}