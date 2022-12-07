struct BCC {
private:
    int n, tot, time;
    vector<vector<int>> g, bcc, tree;
    vector<int> in, low, id, art;
    stack<int> stk;
    void dfs(int u, int p) {
        in[u] = low[u] = time++;
        stk.push(u);
        for (int v : g[u]) {
            if (v == p) continue;
            if (in[v] != -1) low[u] = min(low[u], in[v]);
            else {
                dfs(v, u);

                low[u] = min(low[u], low[v]);
                if (low[v] >= in[u]) {
                    int x;
                    do {
                        x = stk.top();
                        stk.pop();
                        bcc[x].push_back(tot);
                    } while (x != v);
                    bcc[u].push_back(tot++);
                }
            }
        }
    }
public:
    void solve() {
        for (int i = 0; i < n; ++i)
            if (in[i] == -1) dfs(i, -1);
        for (int i = 0; i < n; ++i) {
            if ((int)bcc[i].size() > 1) {
                id[i] = tot++;
                assert(tot <= tree.size());
                art[id[i]] = 1;
                for (int v : bcc[i]) {
                    tree[id[i]].push_back(v);
                    tree[v].push_back(id[i]);
                }
            }
            else if ((int)bcc[i].size() == 1)
                id[i] = bcc[i][0];
        }
    }
    bool isArt(int u) { return art[id[u]]; }
    int getId(int u) { return id[u]; }
    vector<vector<int>> getTree() { return tree; }
    BCC(const vector<vector<int>> &g) : n(g.size()), tot(0), time(0), g(g), bcc(n), tree(2 * n), in(n, -1), low(n), id(n), art(2 * n) { solve(); }
};