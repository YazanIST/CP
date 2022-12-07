// finding path/tour from 0
// all nodes in undirected must have even degree
// if path -> exactly two nodes must have odd degree
// and the graph must be connected (nodes with more than 0 deg must be in one comp)
vector<vector<pair<int,int>>> adj(n); // first is v, second is id
vector<int> path, curEdge(n);
vector<bool> visEdge(m);
stack<int> st;
st.push(0); // push the start

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