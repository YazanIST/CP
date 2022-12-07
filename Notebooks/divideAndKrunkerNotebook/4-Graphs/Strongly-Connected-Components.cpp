class SccSolver {
    int n, cmpCount;
    vector<int> cmpIds;
    vector<vector<int>> adj;
 
    void getSCComponents() {
        stack<int> st;
        vector<bool> inStack(n);
        vector<int> dfsNum(n), dfsLow(n);
        int dfsTime = 0;
 
        function<void(int)> dfs=[&](int v) {
            dfsNum[v] = dfsLow[v] = ++dfsTime;
            st.push(v);
            inStack[v] = true;
 
            for (auto u: adj[v]) {
                if (!dfsNum[u]) {
                    dfs(u);
                }
 
                if (inStack[u]) {
                    dfsLow[v] = min(dfsLow[v], dfsLow[u]);
                }
            }
 
            if (dfsLow[v] == dfsNum[v]) {
                while(true) {
                    int u = st.top();
                    st.pop();
                    inStack[u] = false;
                    cmpIds[u] = cmpCount;
                    if (v == u) {
                        break;
                    }
                }
                cmpCount++;
            }
        };
 
        for (int i = 0; i < n; i++) {
            if (!dfsNum[i]) {
                dfs(i);
            }
        }
    }
public:
    SccSolver (vector<vector<int>> graph) {
        this->adj = graph;
        this->n = graph.size();
        cmpIds.resize(n);
        cmpCount = 0;
        getSCComponents();
    }
 
    int getCmpCount() {
        return cmpCount;
    }
 
    vector<int> getCmpIds() {
        return cmpIds;
    }
 
    int getId(int i) {
        return cmpIds[i];
    }
 
    vector<vector<int>> getDAG() {
        vector<vector<int>> newAdj(getCmpCount());
        for (int i = 0; i < n; i++) {
            for (auto u: adj[i]) {
                if (getId(u) == getId(i)) continue;
                newAdj[getId(i)].push_back(getId(u));
            }
        }
 
        for (auto &list: adj) {
            sort(list.begin(), list.end());
            list.resize(unique(list.begin(), list.end()) - list.begin());
        }
 
        return newAdj;
    }
};