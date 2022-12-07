class Hld {
public:
    Hld(const vector<vector<int>> g)
        : n(g.size()), g(g), dfn(n), depth(n), par(n), sz(n, 1), rev(n), chainRoot(n) {
        iota(chainRoot.begin(), chainRoot.end(), 0);
        init();
    }

    // fun(path_start, path_end)
    template <class E>
    void traverse(int u, int v, const E &fun) {
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
        // NOTE: dont use static for multiple testcases, use an atribute id
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