// Your task is to determine for each node the maximum distance to another node.
void fill(int v, int p, const int idx) {
    for (auto u : adj[v]) {
        if (u == p) continue;
        dis[idx][u] = dis[idx][v] + 1;
        fill(u, v, idx);
    }
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    fill(0, -1, 0);
    fill(max_element(dis[0].begin(), dis[0].end()) - dis[0].begin(), -1, 1);
    fill(max_element(dis[1].begin(), dis[1].end()) - dis[1].begin(), -1, 2);
    for (int i = 0; i < n; i++) {
        cout << max(dis[1][i], dis[2][i]) << ' ';
    }
}