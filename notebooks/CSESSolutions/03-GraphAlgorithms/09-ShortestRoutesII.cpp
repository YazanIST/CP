// There are n cities and m roads between them. Your task is to process q queries where you have to determine the length of the shortest route between two given cities.
int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> adj(n, vector<ll>(n, INF)), dis(n, vector<ll>(n, INF));
    for (int i = 0; i < m; i++) {
        ll v, u, w;
        cin >> v >> u >> w;
        v--, u--;
        adj[v][u] = adj[u][v] = min(adj[v][u], w);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dis[i][j] = 0;
            else if (adj[i][j]) dis[i][j] = adj[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    while (q--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        if (dis[v][u] == INF) cout << "-1\n";
        else cout << dis[v][u] << '\n';
    }
}