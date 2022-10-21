// determine its girth, i.e., the length of its shortest cycle.
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> adj[n];
    while (m--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    int ans = INF;
    auto getShortestCycle = [&](int source) {
        queue<int> q;
        vector<int> dis(n, INF);
        q.push(source);
        dis[source] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : adj[v]) {
                if (dis[u] == INF) {
                    dis[u] = dis[v] + 1;
                    q.push(u);
                }
                else if (dis[u] >= dis[v]) {
                    ans = min(ans, dis[v] + dis[u] + 1);
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        getShortestCycle(i);
    }
    cout << (ans == INF ? -1 : ans);
}