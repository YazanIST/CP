int main() {
    vector<int> dfsNum(n), dfsLow(n);
    vector<bool> isArticulationPoint(n);
    vector<pair<int,int>> bridges;
    int dfsTime = 0, child = 0;

    function<void(int, int)> findBridgesAndArticulationPoints = [&](int v, int p) {
        dfsNum[v] = ++dfsTime;
        dfsLow[v] = dfsNum[v];

        for (auto u: adj[v]) {
            if (!dfsNum[u]) {
                if (p == -1) {
                    ++child;
                }
                findBridgesAndArticulationPoints(u, v);
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

    findBridgesAndArticulationPoints(0, -1);
    isArticulationPoint[0] = child > 1;
}