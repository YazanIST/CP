// Given an array of n integers, your task is to process q queries of the following types:
// 1 update the value at position k to u
// 2 what is the maximum prefix sum in range [a,b]?
class SegmentTree {
private:
    struct Node {
        ll sum, bestPrefix;
        Node(int x = 0) {
            sum = x;
            bestPrefix = max(0ll, sum);
        }

        Node(const Node &lhs, const Node &rhs) {
            sum = lhs.sum + rhs.sum;
            bestPrefix = max(lhs.sum + rhs.bestPrefix, lhs.bestPrefix);
        }
    };
    int n;
    Node seg[N * 4];
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
    void update(int p, int l, int r, int index, int value) {
        if (l == r) {
            seg[p] = Node(value);
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            update(p * 2, l, mid, index, value);
        } else {
            update(p * 2 + 1, mid + 1, r, index, value);
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
        return Node(get(p * 2, l, mid, a, b), get(p * 2 + 1, mid + 1, r, a, b));
    }
public:
    SegmentTree(int n, const vector<int> &a) {
        this->n = n;
        build(1, 0, n - 1, a);
    }
    void update(int index, int value) {
        update(1, 0, n - 1, index, value);
    }
    ll get(int l, int r) {
        return get(1, 0, n - 1, l, r).bestPrefix;
    }
};
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)  cin >> x;
    SegmentTree seg(n, a);
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            seg.update(a - 1, b);
        } else {
            cout << seg.get(a - 1, b - 1) << '\n';
        }
    }
}