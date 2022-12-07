// SCC Solver
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