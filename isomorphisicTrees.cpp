#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7, PRIME = 31;
const int N = 2e5 + 10;
vector<int> powers;

inline int add(int a, int b) {
    return (a + b) % MOD; 
}

inline int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

inline int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int power(int x, int p) {
    int ret = 1;
    while (p > 0) {
        if (p % 2) 
            ret = mul(ret, x);
        p /= 2;
        x = mul(x, x);
    }
    return ret;
}

int inv(int x) {
    return power(x, MOD - 2);
}

inline int divide(int a, int b) {
    return mul(a, inv(b));
}

void calcPowers(){
    powers.push_back(1);
    for (int i = 0; i < N; i++) {
        powers.push_back(mul(powers.back(), PRIME));
    }
}

// dependency: ModularArithmetic
struct Tree {
    int size, root = 0;
    vector<vector<int>> adj;
    vector<int> subtreeSize;
 
    Tree(int size) {
        this->size = size;
        adj.resize(size);
        subtreeSize.resize(size);
    }

    Tree(vector<vector<int>> adj) {
        this->adj = adj;
        size = adj.size();
        subtreeSize.resize(size);
    }
 
    void readTree() {
        for (int i = 1; i < size; i++) {
            int v, u;
            cin >> v >> u;
            v--, u--;
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
    }

    void readFromParents() {
        for (int v = 0; v < size; v++) {
            int u;
            cin >> u;
            u--;
            if (u == -1) {
                root = v;
            } else {
                adj[v].push_back(u);
                adj[u].push_back(v);
            }
        }
    }
 
    vector<int> findCenter() {
        vector<int> deg(size);
        vector<int> leaves;
 
        for (int v = 0; v < size; v++) {
            deg[v] = adj[v].size();
            if (deg[v] <= 1) {
                deg[v] = 0;
                leaves.push_back(v);
            }
        }
 
        int doneLeaves = leaves.size();
 
        while (doneLeaves < size) {
            vector<int> newLeaves;
            for (auto leaf: leaves) {
                for (auto u: adj[leaf]) {
                    if (--deg[u] == 1) {
                        newLeaves.push_back(u);
                    }
                }
                deg[leaf] = 0;
            }
 
            doneLeaves += newLeaves.size();
            leaves = newLeaves;
        }
 
        return leaves;
    }
 
    int encodeTree(int v, int p) {
        vector<pair<int, int>> lables;
        subtreeSize[v] = 1;
        for (auto u: adj[v]) {
            if (u == p) continue;
            lables.push_back({encodeTree(u, v), u});
            subtreeSize[v] += subtreeSize[u];
        }
        sort(lables.begin(), lables.end());
        int ret = 0, shift = 1;
        for (auto [lable, u]: lables) {
            ret = add(ret, mul(powers[shift], lable));
            shift += subtreeSize[u] * 2;
        }
        ret = add(ret, powers[shift]);
        return ret;
    }
 
    vector<int> encodeTree() {
        vector<int> ret;
        for (auto center: findCenter()) {
            ret.push_back(encodeTree(center, -1));
        }
        return ret;
    }

    ll getHash() {
        ll ret = 1;
        for (auto center: encodeTree()) {
            ret *= center;
        }
        return ret;
    }

    // unrooted trees, finds 1 or 2 centers
    bool areIsomorphic(Tree &other) {
        int thisEncode = encodeTree()[0];
        for (auto otherEncode: other.encodeTree()) {
            if (thisEncode == otherEncode) {
                return true;
            }
        }
        return false;
    }
 
    // rooted at 0
    // bool areIsomorphic(Tree &other) {
    //     return encodeTree(root, -1) == other.encodeTree(root, -1);
    // }
};