// There are n buildings on a street, numbered 1,2,…,n. Each building has a pizzeria and an apartment.
// The pizza price in building k is pk. If you order a pizza from building a to building b, its price (with delivery) is pa+|a−b|.
// Your task is to process two types of queries:
// 1 The pizza price pk in building k becomes x.
// 2 You are in building k and want to order a pizza. What is the minimum price?
template <int Sign>
class SegmentTree {
private:
    int n;
    vector<int> seg;
    void build(int p, int l, int r, const vector<int> &a) {
        if (l == r) {
            seg[p] = a[l] + Sign * (l + 1);
            return;
        }
        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid + 1, r, a);
        seg[p] = min(seg[p * 2], seg[p * 2 + 1]);
    }
    int get(int p, int l, int r, int a, int b) {
        if (a <= l && r <= b) {
            return seg[p];
        }
        if (l > b || r < a) {
            return INF;
        }
        int mid = l + (r - l) / 2;
        return min(get(p * 2, l, mid, a, b), get(p * 2 + 1, mid + 1, r, a, b));
    }
    void update(int p, int l, int r, int index, int x) {
        if (l == r) {
            seg[p] = x + (index + 1) * Sign;
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            update(p * 2, l, mid, index, x);
        } else {
            update(p * 2 + 1, mid + 1, r, index, x);
        }
        seg[p] = min(seg[p * 2], seg[p * 2 + 1]);
    }
public:
    SegmentTree(const vector<int> &a) {
        n = a.size();
        seg = vector<int>(n * 4);
        build(1, 0, n - 1, a);
    }
    int get(int l, int r) {
        return get(1, 0, n - 1, l, r);
    }
    void update(int index, int x) {
        update(1, 0, n - 1, index, x);
    }
};
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    SegmentTree<+1> after(a);
    SegmentTree<-1> before(a);
    auto update = [&](int index, int x) {
        after.update(index, x);
        before.update(index, x);
    };
    auto get = [&](int index) {
        int right = after.get(index, n - 1);
        int left = before.get(0, index);
        return min(left + (index + 1), right - (index + 1));
    };
    while (q--) {
        int type, index;
        cin >> type >> index;
        index--;
        if (type == 1) {
            int x;
            cin >> x;
            update(index, x);
        } else {
            cout << get(index) << '\n';
        }
    }
}