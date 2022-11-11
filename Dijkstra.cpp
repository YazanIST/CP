#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class Dijkistra{
    int n;
    vector<ll> dis;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    vector<vector<pair<int, int>>> adj;

    Dijkistra() {
        // assigne n and dis sizes
    }

    void solve() {
        while (!pq.empty()) {
            int v = pq.top().second;
            ll vw = pq.top().first;
            pq.pop();

            if (vw != dis[v]) continue;

            for (auto &[w, u]: adj[v]) {
                if(w + dis[v] < dis[u]) {
                    dis[u] = dis[v] + w;
                    pq.push({dis[u], u});
                }
            }
        }
    }
};