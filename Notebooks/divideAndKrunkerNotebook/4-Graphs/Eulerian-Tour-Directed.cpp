// here the path must start in 1 and end in n, edit if it's okay to start from any node
// here, all nodes must have inDeg = outDeg to have a tour
// if path -> one node exactly must have outDeg - inDeg = 1 (start node)
// and one node exactly must have inDeg - outDeg = 1 (end node)
function<bool()> checkEulerian = [&]() -> bool {
    vector<int> inDeg(n), outDeg(n);
    for (int v = 0; v < n; v++) {
        for (auto u: adj[v]) {
            inDeg[u]++;
            outDeg[v]++;
        }
    }
    
    for (int v = 1; v < n - 1; v++) {
        if (inDeg[v] != outDeg[v]) {
            return false;
        }
    }

    if (outDeg[0] - inDeg[0] != 1) {
        return false;
    }

    if (inDeg[n - 1] - outDeg[n - 1] != 1) {
        return false;
    }

    vector<bool> vis(n);
    function<int(int)> dfs = [&](int v) -> int {
        vis[v] = true;
        int ret = 1;
        for (auto u: adj[v]) {
            if (vis[u]) continue;
            ret += dfs(u);
        }
        return ret;
    };

    int compCnt = 0, onesCount = 0;
    for (int v = 0; v < n; v++) {
        if (vis[v]) continue;
        onesCount += (dfs(v) == 1);
        compCnt++;
    }

    if (compCnt - onesCount != 1) {
        return false;
    }

    return true;
};

if (!checkEulerian()) {
    cout << "IMPOSSIBLE";
    return 0;
}

vector<int> path, curEdge(n);
stack<int> st;

st.push(0);

while (!st.empty()) {
    int v = st.top();
    if (curEdge[v] < (int) adj[v].size()) {
        st.push(adj[v][curEdge[v]++]);
    } else {
        path.push_back(v);
        st.pop();
    }
}