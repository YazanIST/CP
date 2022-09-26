#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

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

class TwoSatSolver {
    int n;
    vector<vector<int>> adj;
    vector<bool> res;

    void compressGraph() {
        for (auto &list: adj) {
            sort(list.begin(), list.end());
            list.resize(unique(list.begin(), list.end()) - list.begin());
        }
    }

    void addDisjunction(int a, bool as, int b, bool bs) {
        a = (a << 1) ^ as;
        b = (b << 1) ^ bs;
        adj[a ^ 1].push_back(b);
        adj[b ^ 1].push_back(a);
    }
public:
    TwoSatSolver(int n) {
        this->n = n;
        adj.resize(n * 2);
        res.resize(n);
    }

    // At least one of them is true
    void addOr(int a, bool as, int b, bool bs) {
        addDisjunction(a, as, b, bs);
    }

    // Both of them have the same value
    void addAnd(int a, bool as, int b, bool bs) {
        addDisjunction(a, !as, b, bs);
        addDisjunction(a, as, b, !bs);
    }

    // Only one of them is true
    void addXOR(int a, bool as, int b, bool bs) {
        addDisjunction(a, as, b, bs);
        addDisjunction(a, !as, b, !bs);
    }

    // Must be true
    void addForce(int a, bool as) {
        addDisjunction(a, as, a, as);
    }

    bool isSatisfiable() {
        compressGraph();
        SccSolver sccSolver(adj);
        for (int i = 0; i < n * 2; i += 2) {
            if (sccSolver.getId(i) == sccSolver.getId(i ^ 1)) {
                return false;
            } else {
                res[i / 2] = (sccSolver.getId(i) > sccSolver.getId(i ^ 1));
            }
        }

        return true;
    }

    vector<bool> getRes() {
        return res;
    }
};