class DSU {
    vector<int> root;
    
public:
    DSU(int n) {
        root.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            root[i] = i;
        }
    }

    int find(int u) {
        if(root[u] == u) 
            return u;
        return root[u] = find(root[u]);
    }

    void connect(int a, int b) {
        a = find(a);
        b = find(b);
        root[a] = root[b];
    }
};
Footer
