// The diameter of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the tree.
int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    vector<int> dpDown(n), dpUp(n);
    function<void(int, int)> dfs = [&](int v, int p) {
        vector<int> cur;
        for (auto u: adj[v]) {
            if (u == p) continue;
            dfs(u, v);
            dpDown[v] = max(dpDown[v], dpDown[u] + 1);
            cur.push_back(dpDown[u]);
        }
        int count = cur.size();
        sort(cur.begin(), cur.end());
        if (count > 1) {
            dpUp[v] = cur[count - 1] + cur[count - 2] + 2;
        } else if (count == 1) {
            dpUp[v] = cur[count - 1] + 1;
        }
    };
    dfs(0, -1);
    cout << *max_element(dpUp.begin(), dpUp.end());
}
//////////////////////////////
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
    cout << *max_element(dis[1].begin(), dis[1].end());
}