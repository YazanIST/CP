// There are n cities and m flight connections between them. Your task is to determine the length of the shortest route from Syrjälä to every city.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[n];
    vector<ll> dis(n, INF);
    vector<bool> vis(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }
    priority_queue<pair<ll, int>> q;
    dis[0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (vis[a]) continue;
        vis[a] = true;
        for (auto u : adj[a]) {
            int b = u.first;
            int w = u.second;
            if (w + dis[a] < dis[b]) {
                dis[b] = dis[a] + w;
                q.push({-dis[b], b});
            }
        }
    }
    for (auto x : dis) cout << x << ' ';
}