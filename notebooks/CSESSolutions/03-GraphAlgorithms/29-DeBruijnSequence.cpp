// Your task is to construct a minimum-length bit string that contains all possible substrings of length n. For example, when n=2, the string 00110 is a valid solution, because its substrings of length 2 are 00, 01, 10 and 11.
int main() {
    int n;
    cin >> n;
    n--;
    int nodes = (1 << n);
    vector<vector<int>> adj(nodes + 1);
    for (int v = 0; v < nodes; v++) {
        int u;
        u = (v << 1);
        u &= ~(1 << n);
        adj[v].push_back(u);
        u ^= 1;
        adj[v].push_back(u);
    }
    vector<int> path, curEdge(nodes + 1);
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int v = st.top();
        if (curEdge[v] < (int) adj[v].size()) {
            st.push(adj[v][curEdge[v]++]);
        } else {
            st.pop();
            path.push_back(v);
        }
    }
    vector<int> ans;
    reverse(path.begin(), path.end());
    for (int i = 1; i < (int) path.size(); i++) {
        ans.push_back(path[i] & 1);
    }
    for (int i = n - 1; i >= 0; i--) {
        cout << bool((1 << i) & path[0]);
    }
    for (auto bit: ans) {
        cout << bit;
    }
}