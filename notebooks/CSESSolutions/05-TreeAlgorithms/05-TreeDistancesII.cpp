// Your task is to determine for each node the sum of the distances from the node to all other nodes.
// lazy segtree here
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
    vector<int> tour, subtreeSize(n), depth(n), inTime(n);
    int timer = 0;
    function<void(int, int, int)> fill = [&](int v, int p, int dep) {
        depth[v] = dep;
        subtreeSize[v] = 1;
        tour.push_back(v);
        inTime[v] = timer++;
        for (auto u: adj[v]) {
            if (u == p) continue;
            fill(u, v, dep + 1);
            subtreeSize[v] += subtreeSize[u];
        }
    };
    fill(0, -1, 0);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = depth[tour[i]];
    }
    LazySegmentTree segtree(a);
    auto increaseSubtree = [&](int v, int val) {
        segtree.update(inTime[v], inTime[v] + subtreeSize[v] - 1, val);
    };
    auto getSubtree = [&](int v) {
        return segtree.get(inTime[v], inTime[v] + subtreeSize[v] - 1).ans;
    };
    vector<ll> ans(n);
    function<void(int, int)> calc = [&](int v, int p) {
        ans[v] = getSubtree(0);
        for (auto u: adj[v]) {
            if (u == p) continue;
            increaseSubtree(0, 1);
            increaseSubtree(u, -2);
            calc(u, v);
            increaseSubtree(0, -1);
            increaseSubtree(u, 2);
        }
    };
    calc(0, -1);
    for (auto x: ans) {
        cout << x << ' ';
    }
}