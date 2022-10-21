// Your task is to find a minimum-price flight route from Syrjälä to Metsälä.
// You have one discount coupon, using which you can halve the price of
// any single flight during the route. However, you can only use the coupon once.
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<ll, int>>> adj(n);
    vector<vector<pair<ll, int>>> revAdj(n);
    vector<pair<pair<int, int>, ll>> edges;
    while (m--) {
        int v, u, w;
        cin >> v >> u >> w;
        v--, u--;
        adj[v].push_back({w, u});
        revAdj[u].push_back({w, v});
        edges.push_back({{v, u}, w});
    }
    function<vector<ll>(int, vector<vector<pair<ll, int>>>)> findCost = [&]
            (int src, vector<vector<pair<ll, int>>> adj) -> vector<ll> {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({0, src});
        vector<ll> ret(n, INF);
        vector<bool> vis(n);
        ret[src] = 0;
        while (!pq.empty()) {
            int v = pq.top().second;
            pq.pop();
            if (vis[v]) continue;
            vis[v] = true;
            for (auto [w, u] : adj[v]) {
                if (ret[u] > ret[v] + w) {
                    ret[u] = ret[v] + w;
                    pq.push({ret[u], u});
                }
            }
        }
        return ret;
    };
    vector<ll> costFromFirst(findCost(0, adj));
    vector<ll> costFromLast(findCost(n - 1, revAdj));
    ll ans = INF;
    for (auto edge : edges) {
        auto [v, u] = edge.first;
        auto w = edge.second;
        ans = min(ans, costFromFirst[v] + costFromLast[u] + w / 2);
    }
    cout << ans;
}