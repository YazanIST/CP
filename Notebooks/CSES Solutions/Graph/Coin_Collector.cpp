// A game has n rooms and m tunnels between them. Each room
// has a certain number of coins. What is the maximum number
// of coins you can collect while moving through the tunnels
// when you can freely choose your starting and ending room?

// strongly connected components
// getToposort
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> coins(n);
    for (auto &x : coins) cin >> x;
    vector<vector<int>> graph(n);
    while (m--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        graph[v].push_back(u);
    }
    SccFinder sccFinder(graph); // graph is passed in 0-index
    vector<int> compIds(sccFinder.getCmpIds());
    vector<vector<int>> adj(sccFinder.getCmpCount());
    vector<vector<int>> adjInv(sccFinder.getCmpCount());
    for (int i = 0; i < n; i++) {
        for (auto u : graph[i]) {
            if (compIds[i] == compIds[u]) continue;
            adj[compIds[i]].push_back(compIds[u]);
            adjInv[compIds[u]].push_back(compIds[i]);
        }
    }
    for (auto &list : adj) {
        set<int> st(set<int>(list.begin(), list.end()));
        list = vector<int>(st.begin(), st.end());
    }
    vector<ll> compCoins(sccFinder.getCmpCount());
    for (int i = 0; i < n; i++) {
        compCoins[compIds[i]] += coins[i];
    }
    vector<int> toposort(getToposort(adj));
    vector<ll> dp(sccFinder.getCmpCount());
    for (auto v : toposort) {
        dp[v] += compCoins[v];
        ll add = 0;
        for (auto u : adjInv[v]) {
            add = max(dp[u], add);
        }
        dp[v] += add;
    }
    cout << *max_element(dp.begin(), dp.end());
}