#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
vector<ll> vals;
vector<vector<int>> adj;
vector<ll> ttaPath;
vector<int> ttaNodeId, ttaSize, ttaidx;


template <typename T>
T sumFunc(T a, T b)
{
    return a + b;
}

enum QueryType { ADD, SET, NONE };

struct Query {
	QueryType type = NONE;
	ll val = 0;
};

template <typename T> class LazySegtree {
    private:
      const int sz;
      vector<T> tree;      // tree[i] = sum of this node's range
      vector<Query> lazy;  // lazy[i] = lazy update for the range
  
      /** builds the segtree nodes */
      void build(int v, int l, int r, const vector<T> &a) {
          if (l == r) {
              tree[v] = a[l];
          } else {
              int m = (l + r) / 2;
              build(2 * v, l, m, a);
              build(2 * v + 1, m + 1, r, a);
              tree[v] = tree[2 * v] + tree[2 * v + 1];
          }
      }
  
      /** applies lazy update to tree[v], places update at lazy[v] */
      void apply(int v, int len, const Query &x) {
          if (x.type == ADD) {
              // if lazy[v]'s type is NONE or ADD, then we add to the range
              // otherwise, we add to our lazy set value
              if (lazy[v].type != SET) {
                  lazy[v] = Query{ADD, lazy[v].val + x.val};
              } else {
                  lazy[v] = Query{SET, lazy[v].val + x.val};
              }
              tree[v] += x.val * len;
          } else if (x.type == SET) {
              // lazy set overrides any previous update
              tree[v] = x.val * len;
              lazy[v] = x;
          }
      }
  
      /** pushes down lazy update to children of v */
      void push_down(int v, int l, int r) {
          int m = (l + r) / 2;
          apply(2 * v, m - l + 1, lazy[v]);
          apply(2 * v + 1, r - m, lazy[v]);
          lazy[v] = Query();
      }
  
      void range_update(int v, int l, int r, int ql, int qr, const Query &x) {
          if (qr < l || ql > r) { return; }
          if (ql <= l && r <= qr) {
              apply(v, r - l + 1, x);
          } else {
              push_down(v, l, r);
              int m = (l + r) / 2;
              range_update(2 * v, l, m, ql, qr, x);
              range_update(2 * v + 1, m + 1, r, ql, qr, x);
              tree[v] = tree[2 * v] + tree[2 * v + 1];
          }
      }
  
      T range_sum(int v, int l, int r, int ql, int qr) {
          if (qr < l || ql > r) { return 0; }
          if (l >= ql && r <= qr) { return tree[v]; }
          push_down(v, l, r);
          int m = (l + r) / 2;
          return range_sum(2 * v, l, m, ql, qr) + range_sum(2 * v + 1, m + 1, r, ql, qr);
      }
  
    public:
      LazySegtree(const vector<T> &a) : sz(a.size()), tree(4 * sz), lazy(4 * sz) {
          build(1, 0, sz - 1, a);
      }
  
      /** updates [ql, qr] with the update x */
      void range_update(int ql, int qr, const Query &x) {
          range_update(1, 0, sz - 1, ql, qr, x);
      }
  
      /** sum of array values on [ql, qr] */
      T range_sum(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }
  };

int dfs(int root, int parent, ll pathSum){
    ttaNodeId.push_back(root);
    pathSum += vals[root];
    ttaPath.push_back(pathSum);
    int idx = ttaSize.size();
    ttaSize.push_back(1);
    for(auto nei : adj[root]){
        if(nei == parent) continue;
        ttaSize[idx] += dfs(nei, root, pathSum);
    }
    return ttaSize[idx];
}

int main(){
    cin >> n >> m;
    adj = vector<vector<int>>(n + 1, vector<int>());
    vals = vector<ll>(n + 1, 0);
    for(int i = 1; i < n + 1; i++){
        cin >> vals[i];
    }
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0, 0);

    LazySegtree<ll> st(ttaPath);
    ttaidx = vector<int>(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        ttaidx[ttaNodeId[i]] = i;
    }
    
    for (int i = 0; i < m; i++)
    {
        int qrytype;
        cin >> qrytype;
        if (qrytype == 2)
        {
            int root;
            cin >> root;
            cout << st.range_sum(ttaidx[root], ttaidx[root]) << endl;
        }
        else
        {
            int a;
            ll val;
            cin >> a >> val;
            ll diff = val - vals[a];
            vals[a] = val;
            st.range_update(ttaidx[a], ttaidx[a] + ttaSize[ttaidx[a]] - 1, Query{ADD, diff});
        }
    }
}