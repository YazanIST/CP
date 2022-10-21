// toposort dfs
// You have to complete n courses. There are m
// requirements of the form "course a has to be
// completed before course b". Your task is to find
// an order in which you can complete the courses.
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
        adj[a].emplace_back(b);
    }
    vector<int> status(n, UNVISITED), ans;
    function<bool(int)> findTopoSort = [&](int v) -> bool {
        status[v] = ONSTACK;
        for (auto u : adj[v]) {
            if (status[u] == ONSTACK) {
                return false;
            } else if (status[u] == UNVISITED && !findTopoSort(u)) {
                return false;
            }
        }
        status[v] = VISITED;
        ans.emplace_back(v);
        return true;
    };
    for (int v = 0; v < n; v++) {
        if (status[v] == UNVISITED) {
            if (!findTopoSort(v)) {
                cout << "IMPOSSIBLE";
                return 0;
            }
        }
    }
    for (auto x : vector<int>(ans.rbegin(), ans.rend())) {
        cout << x + 1 << ' ';
    }
}