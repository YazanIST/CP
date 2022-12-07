// A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?
int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    vector<vector<int>> dp(n, vector<int>(2, -1));
    function<int(int, int, bool)> calc = [&](int v, int p, bool pick) -> int {
        int &ret = dp[v][pick];
        if (ret != -1) {
            return ret;
        }
        ret = 0;
        if (pick) {
            int all = calc(v, p, false);
            for (auto u: adj[v]) {
                if (u == p) continue;
                // here it can be done with prefix and suffix sum to uninclude u
                ret = max(ret, all - calc(u, v, true) + 1 + calc(u, v, false));
            }
        } else {
            for (auto u: adj[v]) {
                if (u == p) continue;
                ret += max(calc(u, v, false), calc(u, v, true));
            }
        }
        return ret;
    };
    cout << max(calc(0, -1, 0), calc(0, -1, 1));
}