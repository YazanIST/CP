// You are given a tree consisting of n nodes. The nodes are numbered 1,2,…,n.
// Each node has a value.
// Your task is to process following types of queries:
// change the value of node s to x
// find the maximum value on the path between nodes a and b.
template <typename T, class F>
class segtree {
 public:
  segtree() = default;
  segtree(int n, const F &combine, const T &neutral) : segtree(std::vector<T>(n, neutral), combine, neutral) {}
  segtree(const std::vector<T> &v, const F &combine, const T &neutral) : n(v.size()), combine(combine), NEUTRAL(neutral) {
    size = 1;
    while (size < n) size *= 2;
    tree.resize(2 * size, NEUTRAL);
    for (int i = 0; i < n; ++i) tree[i + size] = v[i];
    for (int i = size - 1; i > 0; --i) pull(i);
  }
  void set(int i, T v) {
    i += size;
    tree[i] = v;
    while (i > 1) {
      i /= 2;
      pull(i);
    }
  }
  T get(int i) { return tree[i + size]; }
  T prod(int l, int r) {
    T leftRes(NEUTRAL);
    T rightRes(NEUTRAL);
    for (l += size, r += size; l <= r; l /= 2, r /= 2) {
      if (l % 2 == 1) leftRes = combine(leftRes, tree[l++]);
      if (r % 2 == 0) rightRes = combine(tree[r--], rightRes);
    }
    return combine(leftRes, rightRes);
  }
  T allProd() { return tree[1]; }
 private:
  void pull(int i) { tree[i] = combine(tree[2 * i], tree[2 * i + 1]); }
  std::vector<T> tree;
  int n, size;
  F combine;
  const T NEUTRAL;
};
 
class Hld {
 public:
  Hld(const vector<vector<int>> g)
      : n(g.size()), g(g), dfn(n), depth(n), par(n), sz(n, 1), rd(n), chainRoot(n) {
    iota(chainRoot.begin(), chainRoot.end(), 0);
    init();
  }
 
  // fun(path_start, path_end)
  template <class E> void traverse(int u, int v, const E &fun) {
    while (chainRoot[u] != chainRoot[v]) {
      if (depth[chainRoot[u]] < depth[chainRoot[v]]) {
        swap(u, v);
      }
      fun(dfn[chainRoot[u]], dfn[u]);
      u = par[chainRoot[u]];
    }
    if (depth[u] < depth[v]) {
      swap(u, v);
    }
    fun(dfn[v], dfn[u]);
  }
 
  int getLca(int u, int v) {
    int res;
    traverse(u, v, [&](int l, int _) {
      res = rd[l];
    });
    return res;
  }
 
  int getDist(int u, int v) {
    int res = -1;
    traverse(u, v, [&](int l, int r) {
      res += r - l + 1;
    });
    return res;
  }
 
 private:
  void init() {
    dfs(0, -1);
    chainRoot[0] = 0;
    dfsHld(0, -1);
  }
 
  void dfs(int u, int p) {
    for (int v : g[u]) {
      if (v == p) {
        continue;
      }
      par[v] = u;
      depth[v] = depth[u] + 1;
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
 
  void dfsHld(int u, int p) {
    static int id = 0;
    rd[id] = u;
    dfn[u] = id++;
    int bigChild = -1;
    for (int v : g[u]) {
      if (v == p) {
        continue;
      }
      if (bigChild == -1 || sz[v] > sz[bigChild]) {
        bigChild = v;
      }
    }
    if (bigChild != -1) {
      chainRoot[bigChild] = chainRoot[u];
      dfsHld(bigChild, u);
    }
    for (int v : g[u]) {
      if (v == p || v == bigChild) {
        continue;
      }
      chainRoot[v] = v;
      dfsHld(v, u);
    }
  }
 
  int n;
  vector<vector<int>> g;
  vector<int> dfn, depth, par, sz, rd, chainRoot;
};
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  Hld hld(g);
  segtree seg(n, [](int a, int b) { return max(a, b); }, numeric_limits<int>::min()); 
  auto updateNode = [&](int u, int val) {
    hld.traverse(u, u, [&](int l, int r) {
      assert(l == r);
      seg.set(l, val);
    });
  };
  auto queryPath = [&](int u, int v) {
    int ret = numeric_limits<int>::min();
    hld.traverse(u, v, [&](int l, int r) {
      ret = max(ret, seg.prod(l, r));
    });
    return ret;
  };
  for (int i = 0; i < n; ++i) {
    updateNode(i, a[i]);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int u, x;
      cin >> u >> x;
      --u;
      updateNode(u, x);
    } else {
      int a, b;
      cin >> a >> b;
      --a, --b;
      int ans = queryPath(a, b);
      cout << ans << ' ';
    }
  }
  cout << '\n';
  return 0;
}