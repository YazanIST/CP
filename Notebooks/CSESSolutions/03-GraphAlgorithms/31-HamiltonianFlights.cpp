// There are n cities and m flight connections between them. You want to travel from Syrjälä to Lehmälä so that you visit each city exactly once. How many possible routes are there?
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
    }
    vector<vector<int>> dp((1 << n), vector<int>(n, -1));
    function<int(int, int)> calc = [&](int mask, int v) -> int {
        if (mask == (1 << n) - 1) {
            return (v == n - 1);
        }
        if (v == n - 1) {
            return 0;
        }
        auto &ret = dp[mask][v];
        if (ret != -1) {
            return ret;
        }
        ret = 0;
        for (auto u: adj[v]) {
            if (mask & (1 << u)) continue;
            ret = add(ret,  calc(mask ^ (1 << u), u));
        }
        return ret;
    };
    cout << calc(1, 0);
}