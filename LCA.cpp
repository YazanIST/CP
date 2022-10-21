class Lca {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> up;
    
    void fill(int v, int p, const vector<vector<int>> &g) {
        for (auto u: g[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            up[u][0] = v;
            for (int i = 1; i < lg; i++) {
                up[u][i] = up[up[u][i - 1]][i - 1];
            }
            fill(u, v, g);
        }
    }

public:
    Lca(const vector<vector<int>> &g, int root = 0): n(g.size()), lg(__lg(n) + 1),
                    depth(g.size()), up(n, vector<int>(lg)) {
        fill(root, -1, g);
    }

    int getKth(int v, int k) {
        for (int i = lg - 1; i >= 0; i--) {
            if (k & (1 << i)) {
                v = up[v][i];
            }
        }
        return v;
    }

    int getLca(int v, int u) {
        if (depth[v] > depth[u]) {
            swap(v, u);
        }

        u = getKth(u, depth[u] - depth[v]);

        if (u == v) {
            return v;
        }

        for (int i = lg - 1; i >= 0; i--) {
            if (up[v][i] != up[u][i]) {
                v = up[v][i];
                u = up[u][i];
            }
        }

        return up[v][0];
    }

    int getDistance(int v, int u) {
        return depth[v] + depth[u] - 2 * depth[getLca(v, u)];
    }

    int getDepth(int v) {
        return depth[v];
    }

    int parent(int v) {
        return up[v][0];
    }
};
