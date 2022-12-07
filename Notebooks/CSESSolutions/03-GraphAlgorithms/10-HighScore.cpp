// You play a game consisting of n rooms and m tunnels. Your initial score is 0, and each tunnel increases your score by x where x may be both positive or negative. You may go through a tunnel several times.
// Your task is to walk from room 1 to room n. What is the maximum score you can get?
struct Edge {
    ll v, u, w;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto &[v, u, w] : edges) {
        cin >> v >> u >> w;
        v--, u--;
    }

    vector<ll> dis(n, -INF);
    dis[0] = 0;

    for (int i = 0; i < 2 * n; i++) {
        for (auto [v, u, w] : edges) {
            if (dis[v] == -INF) continue;
            if (dis[v] + w <= dis[u]) continue;
            dis[u] = max(dis[u], dis[v] + w);
            if (i > n - 1) dis[u] = INF;
        }
    }

    if (dis[n - 1] == INF) cout << -1;
    else cout << dis[n - 1];
}