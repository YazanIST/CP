vector<int> getToposort(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> inDegree(n);
    
    for (int v = 0; v < n; v++) {
        for (auto u: adj[v]) {
            inDegree[u]++;
        }
    }
 
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDegree[i]) {
            q.push(i);
        }
    }
 
    vector<int> toposort;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
 
        toposort.push_back(v);
        for (auto u: adj[v]) {
            inDegree[u]--;
            if (!inDegree[u]) {
                q.push(u);
            }
        }
    }

    if (toposort.size() != adj.size()) {
        // toposort does not exist (not dag)
        return vector<int> {};
    }
 
    return toposort;
}