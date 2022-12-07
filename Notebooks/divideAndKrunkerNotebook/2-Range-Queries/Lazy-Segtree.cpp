struct Node {
    ll ans, lazy;

    Node() {
        ans = lazy = 0;
    }

    Node(int x) {
        ans = x;
        lazy = 0;
    }

    Node(const Node &lhs, const Node &rhs) {
        ans = lhs.ans + rhs.ans;
        lazy = 0;
    }
};

class SegmentTree {
    int n;
    vector<Node> seg;
    
    void propagate(int p, int l, int r) {
        if (seg[p].lazy) {
            if (l != r) {
                seg[p * 2].lazy += seg[p].lazy;
                seg[p * 2 + 1].lazy += seg[p].lazy;
            }
            seg[p].ans += seg[p].lazy * (r - l + 1);
            seg[p].lazy = 0;
        }
    }

    void build(int p, int l, int r, const vector<int> &a) {
        if (l == r) {
            seg[p] = Node(a[l]);
            return;
        }

        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid + 1, r, a);
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }

    void update(int p, int l, int r, int a, int b, int val) {
        propagate(p, l, r);
        if (a <= l && r <= b) {
            seg[p].lazy += val;
            propagate(p, l, r);
            return;
        }

        if (l > b || r < a) {
            return;
        }

        int mid = l + (r - l) / 2;
        update(p * 2, l, mid, a, b, val);
        update(p * 2 + 1, mid + 1, r, a, b, val);
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }

    Node get(int p, int l, int r, int a, int b) {
        propagate(p, l, r);
        if (a <= l && r <= b) {
            return seg[p];
        }

        if (l > b || r < a) {
            return Node();
        }

        int mid = l + (r - l) / 2;
        return Node(get(p * 2, l, mid, a, b),
                    get(p * 2 + 1, mid + 1, r , a, b));
    }

public:
    SegmentTree(const vector<int> &a) {
        this->n = a.size();
        seg.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    void update(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

    Node get(int l, int r) {
        return get(1, 0, n - 1, l, r);
    }

    Node get(int index) {
        return get(index, index);
    }
};