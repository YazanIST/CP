// You are given a directed weighted graph with N nodes and M edges.
// Your task is to find the minimum shortest path between any pair
// of nodes in the graph. As the weight of the edges can be negative,
// the path is allowed to visit the same node multiple times.
struct Edge {
    int a, b, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        edges.push_back({a, b, w});
    }
    vector<ll> dis(n, 0);
    for (int i = 1; i <= n - 1; i++) {
        for (auto &[a, b, w] : edges) {
            dis[b] = min(dis[b], dis[a] + w);
        }
    }
    for (auto &[a, b, w] : edges) {
        if (dis[a] + w < dis[b]) {
            cout << "-inf";
            return;
        }
    }
    ll ans = *min_element(dis.begin(), dis.end());
    if (ans == 0) {
        int minEdge = 1e9;
        for (auto [a, b, w] : edges) {
            minEdge = min(minEdge, w);
        }
        cout << minEdge;
    } else {
        cout << ans;
    }
}