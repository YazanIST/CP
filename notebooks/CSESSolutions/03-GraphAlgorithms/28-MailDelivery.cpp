// Your task is to deliver mail to the inhabitants of a city. For this reason, you want to find a route whose starting and ending point are the post office, and that goes through every street exactly once.
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back({u, i});
        adj[u].push_back({v, i});
    }
    for (int v = 0; v < n; v++) {
        if ((int) adj[v].size() % 2) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    vector<int> path, curEdge(n);
    vector<bool> visEdge(m);
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int v = st.top();
        if (curEdge[v] < (int) adj[v].size()) {
            if (!visEdge[adj[v][curEdge[v]].second]) {
                st.push(adj[v][curEdge[v]].first);
                visEdge[adj[v][curEdge[v]].second] = true;
            }
            curEdge[v]++;
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    if ((int) path.size() != m + 1) {
        cout << "IMPOSSIBLE";
    } else {
        for (auto v: vector<int>(path.rbegin(), path.rend())) {
            cout << v + 1 << ' ';
        }
    }
}