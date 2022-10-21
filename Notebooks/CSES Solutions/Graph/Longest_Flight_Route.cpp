// Uolevi has won a contest, and the prize is a
// free flight trip that can consist of one or more
// flights through cities. Of course, Uolevi wants
// to choose a trip that has as many cities as possible.
// Uolevi wants to fly from Syrjälä to Lehmälä
// so that he visits the maximum number of cities.
// You are given the list of possible flights,
// and you know that there are no directed cycles in the flight network.
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
    vector<int> toposort(getToposort(adj)), dp(n, -INF), parent(n, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = toposort[i];
        for (auto u : adj[v]) {
            if (dp[v] + 1 > dp[u]) {
                dp[u] = dp[v] + 1;
                parent[u] = v;
            }
        }
    }
    vector<int> ans;
    int cur = n - 1;
    while (cur != -1) {
        ans.push_back(cur + 1);
        cur = parent[cur];
    }
    reverse(ans.begin(), ans.end());
    if (ans.front() == 1) {
        cout << ans.size() << '\n';
        for (auto x : ans)
            cout << x << ' ';
    } else {
        cout << "IMPOSSIBLE";
    }
}