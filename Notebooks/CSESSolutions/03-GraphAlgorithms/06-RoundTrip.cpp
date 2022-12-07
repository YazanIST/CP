// Byteland has n cities and m roads between them. Your task is to design a round trip that begins in a city, goes through two or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.
int const N = 1e5 + 1;
int n, m;
vector<int> adj[N], parent(N);
vector<bool> vis(N);

void dfs(int x) {
    vis[x] = true;
    for (auto u : adj[x]) {
        if (!vis[u]) {
            parent[u] = x;
            dfs(u);
        } else {
            int cur = x;
            int count = 0;
            vector<int> ans;
            ans.push_back(u + 1);
            while (cur != u) {
                count++;
                ans.push_back(cur + 1);
                cur = parent[cur];
            }
            ans.push_back(u + 1);
            if (ans.size() > 3) {
                cout << ans.size() << '\n';
                for (int i = 0; i < ans.size(); i++)
                    cout << ans[i] << ' ';
                exit(0);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++)
        if (!vis[i]) dfs(i);
    cout << "IMPOSSIBLE";
}