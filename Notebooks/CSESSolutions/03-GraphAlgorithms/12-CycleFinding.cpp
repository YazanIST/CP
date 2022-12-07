// You are given a directed graph, and your task is to find out if it contains a negative cycle, and also give an example of such a cycle.
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const ll INF = 1e18;

struct Edge {
    ll v, u, w;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto &[v, u, w] : edges) {
        cin >> v >> u >> w;
        v--, u--;
    }
    vector<ll> dis(n);
    vector<int> p(n, -1);
    int last = -1;
    for (int i = 0; i < n - 1; i++) {
        last = -1;
        for (auto [v, u, w] : edges) {
            if (dis[v] == INF) continue;
            if (dis[v] + w >= dis[u]) continue;
            dis[u] = max(-INF, dis[v] + w);
            p[u] = v;
            last = u;
        }
    }

    if (last == -1) cout << "NO";
    else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            last = p[last];
        }
        vector<int> path;
        for (int v = last;; v = p[v]) {
            path.push_back(v);
            if (v == last && path.size() > 1) {
                break;
            }
        }
        reverse(path.begin(), path.end());
        for (auto x : path) cout << x + 1 << ' ';
    }
}