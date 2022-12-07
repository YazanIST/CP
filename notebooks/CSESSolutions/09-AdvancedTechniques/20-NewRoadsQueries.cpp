// There are n cities in Byteland but no roads between them. However, each day, a new road will be built. There will be a total of m roads.
// Your task is to process q queries of the form: "after how many days can we travel from city a to city b for the first time?"

// UnionFind
//NeroHLD
class SegmentTree {
public:
    SegmentTree() {}
    
    SegmentTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size, NEUTRAL);
        for (int i = 0; i < n; ++i) tree[i + size] = 0;
        for (int i = size - 1; i > 0; --i) pull(i);
    }
 
    inline void operator=(const SegmentTree &other) {
        tree = other.tree;
        n = other.n;
        size = other.size;
    }
 
    void update(int i, int v) {
        i += size;
        tree[i] = v;
        while (i > 1) {
            i /= 2;
            pull(i);
        }
    }
 
    int get(int l, int r) {
        int leftRes(NEUTRAL);
        int rightRes(NEUTRAL);
        for (l += size, r += size; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) leftRes = combine(leftRes, tree[l++]);
            if (r % 2 == 0) rightRes = combine(tree[r--], rightRes);
        }
        return combine(leftRes, rightRes);
    }
 
private:
    vector<int> tree;
    int n, size;
    const int NEUTRAL = 0;
 
    void pull(int i) { tree[i] = combine(tree[2 * i], tree[2 * i + 1]); }
 
    int combine(int lhs, int rhs) { return max(lhs, rhs); }
};
 
struct Edge {
    int v;
};
 
struct Tree {
    int size;
    vector<vector<int>> adj;
    vector<int> nodes;
    unordered_map<int, int> nodeId;
    TreeHeavyLightDecomposition hld;
    SegmentTree segtree;
 
    int getNodeId(int v) {
        return lower_bound(nodes.begin(), nodes.end(), v) - nodes.begin();
    }
 
    void build(const vector<vector<pair<int,int>>> &g) {
        size = nodes.size();
        adj.resize(size);
        for (auto v: nodes) {
            nodeId[v] = getNodeId(v);
        }
        for (auto v: nodes) {
            for (auto [u, w]: g[v]) {
                adj[nodeId[v]].push_back(nodeId[u]);
            }
        }
        hld = TreeHeavyLightDecomposition(size);
        hld.graph = adj;
        segtree = SegmentTree(size);
        hld.make();
        vector<int> nodeValue(size);
        for (auto v: nodes) {
            for (auto [u, w]: g[v]) {
                updateEdge(nodeId[v], nodeId[u], w);
            }
        }
    }
 
    int getMoreDepth(int v, int u) {
        if (hld.depth[v] > hld.depth[u]) {
            return v;
        }
        return u;
    }
 
    void updateEdge(int v, int u, int w) {
        hld.traverse([&](int _, int l, int r) {
            segtree.update(r, w);
        }, v, u, false);
    }
 
    int getAns(int v, int u) {
        int ret = 0;
        v = nodeId[v], u = nodeId[u];
        hld.traverse([&](int _, int l, int r) {
            ret = max(ret, segtree.get(l, r));
        }, v, u, false);
        return ret;
    }
};
 
int main(){
    int n, m, q;
    cin >> n >> m >> q;
    UnionFind dsu(n);
    vector<vector<pair<int,int>>> adj(n);
 
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        if (dsu.isSameSet(v, u)) continue;
        dsu.unionSet(v, u);
        adj[v].push_back({u, i + 1});
        adj[u].push_back({v, i + 1});
    }
 
    vector<Tree> trees(dsu.numDisjointSets());
    vector<int> compressed;
 
    for (int v = 0; v < n; v++) {
        compressed.push_back(dsu.findSet(v));
    }
    
    sort(compressed.begin(), compressed.end());
    compressed.resize(unique(compressed.begin(), compressed.end()) - compressed.begin());
 
    auto getTreeId = [&](int v) {
        return lower_bound(compressed.begin(), compressed.end(), dsu.findSet(v)) - compressed.begin();
    };
 
    vector<int> treeId(n);
    for (int v = 0; v < n; v++) {
        treeId[v] = getTreeId(v);
        trees[treeId[v]].nodes.push_back(v);
    }
 
    for (auto &tree: trees) {
        tree.build(adj);
    }
 
    while (q--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        if (dsu.isSameSet(v, u)) {
            cout << trees[getTreeId(v)].getAns(v, u) << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}