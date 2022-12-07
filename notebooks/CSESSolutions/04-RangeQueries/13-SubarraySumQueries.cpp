// There is an array consisting of n integers. Some values of the array will be updated, and after each update, your task is to report the maximum subarray sum in the array.
class SegmentTree {
private:
    struct Node {
        ll ans, sum, bestSuffix, bestPrefix;
        Node(int x = 0) {
            sum = x;
            ans = bestPrefix = bestSuffix = max(0, x);
        }
        Node(const Node &lhs, const Node &rhs) {
            sum = lhs.sum + rhs.sum;
            bestPrefix = max({lhs.bestPrefix, lhs.sum, lhs.sum + rhs.bestPrefix, lhs.sum + rhs.sum});
            bestSuffix = max({rhs.bestSuffix, rhs.sum, rhs.sum + lhs.bestSuffix, rhs.sum + lhs.sum});
            ans = max({lhs.ans, rhs.ans, lhs.bestSuffix + rhs.bestPrefix});
        }
    } seg[N * 4];
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
public:
    SegmentTree(int n, const vector<int> &a) {
        build(1, 0, n - 1, a);
    }
    void update(int p, int l, int r, const int index, const int x) {
        if (l == r) {
            seg[p] = Node(x);
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            update(p * 2, l, mid, index, x);
        } else {
            update(p * 2 + 1, mid + 1, r, index, x);
        }
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }
    ll answer() {
        return seg[1].ans;
    }
};
while (m--) {
    int index, value;
    cin >> index >> value;
    seg.update(1, 0, n - 1, index - 1, value);
    cout << seg.answer() << '\n';
}