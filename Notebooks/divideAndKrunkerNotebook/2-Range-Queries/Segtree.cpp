struct Node {
    int val;

    Node() {
        
    }

    Node(int x) {
    }

    Node(const Node &lhs, const Node &rhs) {
    }
};

class SegmentTree {
    int n;
    vector<Node> seg;
    
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

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            seg[p] = Node(val);
            return;
        }

        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(p * 2, l, mid, idx, val);
        } else {
            update(p * 2 + 1, mid + 1, r, idx, val);
        }
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }

    Node get(int p, int l, int r, int a, int b) {
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

    int firstIdxGreaterThanX(int cur, int s, int e, int x) { // maxSeg
        if (s == e) {
            if(seg[cur].val < x) return -1;
            return s;
        }
 
        int m = (s + e) / 2;
        if (x <= seg[2 * cur].val) {
            return firstIdxGreaterThanX(2 * cur, s, m, x);
        }
        else {
            return firstIdxGreaterThanX(2 * cur + 1, m + 1, e, x);
        }
    }

    int firstIdxEqualX(int cur, int s, int e, int x) { // sumSeg
        if (s == e) {
            if(seg[cur].val != x) return -1;
            return s;
        }
 
        int m = (s + e) / 2;
        if (x <= seg[2 * cur].val) {
            return firstIdxEqualX(2 * cur, s, m, x);
        }
        else {
            x -= seg[2 * cur].val;
            return firstIdxEqualX(2 * cur + 1, m + 1, e, x);
        }
    }

public:
    SegmentTree(const vector<int> &a) {
        this->n = a.size();
        seg.resize(n * 4);
        build(1, 0, n - 1, a);
    }
    
    SegmentTree(int n) {
        this->n = n;
        seg.resize(n * 4);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    Node get(int l, int r) {
        return get(1, 0, n - 1, l, r);
    }

    int findX(int x) {
        return 0;
    }
};