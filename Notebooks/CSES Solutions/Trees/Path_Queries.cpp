// Your task is to process following types of queries:
// change the value of node s to x
// calculate the sum of values on the path from the root to node s
const int N = 2e5 + 1;
int n, q;
vector<int> adj[N], tour, inTime(N), subtreeSize(N);
vector<ll> value(N), sumFromRoot(N);
void dfs(int v, int p) {
    inTime[v] = tour.size();
    tour.push_back(v);
    subtreeSize[v] = 1;
    sumFromRoot[v] = ((p == -1) ? 0 : sumFromRoot[p]) + value[v];
    for (auto u : adj[v]) {
        if (u == p) continue;
        dfs(u, v);
        subtreeSize[v] += subtreeSize[u];
    }
}
// LAZY SEGTREE
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = sumFromRoot[tour[i]];
    }
    LazySegmentTree seg(n, a);
    while (q--) {
        int type, s;
        cin >> type >> s;
        s--;
        if (type == 1) {
            int x;
            cin >> x;
            seg.update(inTime[s], inTime[s] + subtreeSize[s] - 1, x - value[s]);
            value[s] = x;
        } else {
            cout << seg.get(inTime[s]) << '\n';
        }
    }
}