// You need to perform the following two kinds of queries on the tree:
// add t value: Add value to all nodes in subtree rooted at t
// max a b: Report maximum value on the path from a to b
class LazySegmentTree {
 public:
  LazySegmentTree(int n) : n(n) {
    tree.resize(4 * n);
  }

  void update(int l, int r, int val) {
    auto helper = [&](auto self, int p, int s, int e) {
      prop(p, s, e);
      if (s > r || e < l) {
        return;
      }
      if (l <= s && e <= r) {
        tree[p].lazy = val;
        tree[p].pending = true;
        prop(p, s, e);
        return;
      }
      int mid = (s + e) / 2;
      self(self, 2 * p, s, mid);
      self(self, 2 * p + 1, mid + 1, e);
      pull(p);
    };
    helper(helper, 1, 0, n - 1);
  }

  int get(int l, int r) {
    auto helper = [&](auto self, int p, int s, int e) -> int {
      prop(p, s, e);
      if (s > r || e < l) {
        return numeric_limits<int>::min();
      }
      if (l <= s && e <= r) {
        return tree[p].val;
      }
      int mid = (s + e) / 2;
      return max(self(self, 2 * p, s, mid), self(self, 2 * p + 1, mid + 1, e));
    };
    return helper(helper, 1, 0, n - 1);
  }
 
 private:
  struct Node {
    int val;
    int lazy;
    bool pending;
    Node() : val(0), lazy(0), pending(false) {}
    Node(int x) : val(x), lazy(0), pending(false) {}
  };

  void prop(int p, int s, int e) {
    if (!tree[p].lazy) {
      return;
    }
    tree[p].val += tree[p].lazy;
    if (s != e) {
      tree[2 * p].pending = tree[2 * p + 1].pending = true;
      tree[2 * p].lazy += tree[p].lazy;
      tree[2 * p + 1].lazy += tree[p].lazy;
    }
    tree[p].lazy = 0;
    tree[p].pending = false;
  }

  void pull(int p) {
    tree[p].val = max(tree[2 * p].val, tree[2 * p + 1].val);
  }

  int n;
  vector<Node> tree;
};

class Hld {
 public:
  Hld(const vector<vector<int>> g)
      : n(g.size()), g(g), dfn(n), depth(n), par(n), sz(n, 1), rev(n), chainRoot(n) {
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
      res = rev[l];
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
    rev[id] = u;
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
  vector<int> dfn, out, depth, par, sz, rev, chainRoot;
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  LazySegmentTree seg(n);
  Hld hld(g);
  auto queryPath = [&](int u, int v) {
    int ret = numeric_limits<int>::min();
    hld.traverse(u, v, [&](int l, int r) {
      ret = max(ret, seg.get(l, r));
    });
    return ret;
  };
  int q;
  cin >> q;
  while (q--) {
    string type;
    cin >> type;
    if (type == "add") {
      int u, val;
      cin >> u >> val;
      --u;
      int in = hld.dfn[u];
      int out = in + hld.sz[u] - 1;
      seg.update(in, out, val);
    } else {
      int u, v;
      cin >> u >> v;
      --u, --v;
      int ans = queryPath(u, v);
      cout << ans << '\n';
    }
  }
  return 0;
}