// Byteland has n cities and m flight connections. Your task is
// to design a round trip that begins in a city, goes
// through one or more other cities, and finally returns
// to the starting city. Every intermediate city
// on the route has to be distinct.
enum {
    VISITED = 1,
    ONSTACK = 0,
    UNVISITED = -1
};
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    vector<int> backtrack, status(n, UNVISITED);
    function<void(int)> findCycle = [&](int v) {
        status[v] = ONSTACK;
        backtrack.push_back(v);
        for (auto u : adj[v]) {
            if (status[u] == ONSTACK) {
                vector<int> ans;
                while (backtrack.back() != u) {
                    ans.push_back(backtrack.back() + 1);
                    backtrack.pop_back();
                }
                reverse(ans.begin(), ans.end());
                cout << ans.size() + 2 << '\n';
                cout << u + 1 << ' ';
                for (auto x : ans)
                    cout << x << ' ';
                cout << u + 1 << ' ';
                exit(0);
            } else if (status[u] == UNVISITED) {
                findCycle(u);
            }
        }
        backtrack.pop_back();
        status[v] = VISITED;
    };
    for (int i = 0; i < n; i++) {
        if (status[i] == UNVISITED) {
            findCycle(i);
        }
    }
    cout << "IMPOSSIBLE";
}