#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    vector<int> dfsNum(n), dfsLow(n);
    vector<bool> isArticulationPoint(n);
    vector<pair<int,int>> bridges;
    int dfsTime = 0, child = 0;

    function<void(int, int)> findArticulationPoints = [&](int v, int p) {
        dfsNum[v] = ++dfsTime;
        dfsLow[v] = dfsNum[v];

        for (auto u: adj[v]) {
            if (!dfsNum[u]) {
                if (p == -1) {
                    ++child;
                }
                findArticulationPoints(u, v);
                dfsLow[v] = min(dfsLow[v], dfsLow[u]);
                if (dfsLow[u] >= dfsNum[v]) {
                    isArticulationPoint[v] = true;
                }
                if (dfsLow[u] > dfsNum[v]) {
                    bridges.push_back({v, u});
                }
            } else if (u != p) {
                dfsLow[v] = min(dfsLow[v], dfsNum[u]);
            }
        }
    };

    findArticulationPoints(0, -1);
    isArticulationPoint[0] = child > 1;
}
