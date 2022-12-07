// Given a tree of n nodes, your task is to find a centroid, i.e., a node such that when it is appointed the root of the tree, each subtree has at most ⌊n/2⌋ nodes.
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
    vector<int> subtreeSize(n, 1);
    function<void(int, int)> calcSize = [&](int v, int p) {
        for (auto u: adj[v]) {
            if (u == p) continue;
            calcSize(u, v);
            subtreeSize[v] += subtreeSize[u];
        }
    };
    calcSize(0, -1);
    function<int(int, int)> findCentroid = [&](int v, int p) -> int {
        for (auto u: adj[v]) {
            if (u == p) continue;
            if (subtreeSize[u] * 2 > n) {
                return findCentroid(u, v);
            }
        }
        return v + 1;
    };
    cout << findCentroid(0, -1);
}