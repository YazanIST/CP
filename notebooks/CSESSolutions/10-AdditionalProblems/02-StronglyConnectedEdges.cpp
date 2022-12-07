// Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is strongly connected.
int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    vector<bool> edgeVis(m);
    vector<pair<int, int>> ans;
    vector<int> dfsNum(n), dfsLow(n);
    int dfsTime = 0;

    function<bool(int, int)> getAns = [&](int v, int p) -> bool {
        dfsNum[v] = ++dfsTime;
        dfsLow[v] = dfsNum[v];

        for (auto [u, idx] : adj[v]) {
            if (u == p) continue;
            if (!edgeVis[idx]) {
                edgeVis[idx] = true;
                ans.push_back({v + 1, u + 1});
            }
            if (dfsNum[u] == 0) { // unvisited
                if (!getAns(u, v)) {
                    return false;
                }
                dfsLow[v] = min(dfsLow[v], dfsLow[u]);
                if (dfsLow[u] > dfsNum[v]) {
                    return false;
                }
            } else {
                dfsLow[v] = min(dfsLow[v], dfsNum[u]);
            }
        }
        return true;
    };

    if (getAns(0, -1) && (int)ans.size() == m) {
        for (auto [a, b] : ans) {
            cout << a << ' ' << b << '\n';
        }
    } else {
        cout << "IMPOSSIBLE";
    }
}