// A game has n levels, connected by m teleporters, and your task is to get from level 1 to level n. The game has been designed so that there are no directed cycles in the underlying graph. In how many ways can you complete the game?
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    vector<int> toposort(getToposort(adj)), dp(n);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int v = toposort[i];
        for (auto u : adj[v]) {
            dp[u] = add(dp[u], dp[v]);
        }
    }
    cout << dp[n - 1];
}