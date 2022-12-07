// You are given an array of n integers and q queries of the form: how many distinct values are there in a range [a,b]?
class SegmentTree {
    int n;
    vector<int> seg;
    void update(int p, int l, int r, int pos) {
        if (l == r) {
            seg[p] ^= 1;
            return;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            update(p * 2, l, mid, pos);
        } else {
            update(p * 2 + 1, mid + 1, r, pos);
        }
        seg[p] = seg[p * 2] + seg[p * 2 + 1];
    }
    int query(int p, int l, int r, int a, int b) {
        if (a <= l && r <= b) {
            return seg[p];
        }
        if (l > b || r < a) {
            return 0;
        }
        int mid = l + (r - l) / 2;
        return query(p * 2, l, mid, a, b) + query(p * 2 + 1, mid + 1, r, a, b);
    }
public:
    SegmentTree(int n) {
        this->n = n;
        seg.assign(n * 4, 0);
    }
    void update(int index) {
        update(1, 0, n - 1, index);
    }
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
struct Query {
    int l, r, idx, ans;
};
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), comp;
    for (auto &x : a) cin >> x;
    comp = a;
    sort(comp.begin(), comp.end());
    comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
    for (auto &x : a) {
        x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();
    }
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--, queries[i].r--;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end(), [](const Query &lhs, const Query &rhs) { return lhs.r < rhs.r; });
    vector<int> pos(n, -1);
    SegmentTree segtree(n);
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (pos[a[i]] != -1) {
            segtree.update(pos[a[i]]);
        }
        pos[a[i]] = i;
        segtree.update(pos[a[i]]);
        while (r < q && queries[r].r == i) {
            queries[r].ans = segtree.query(queries[r].l, queries[r].r);
            r++;
        }
    }
    sort(queries.begin(), queries.end(), [](const Query &lhs, const Query &rhs) { return lhs.idx < rhs.idx; });
    for (auto query : queries) {
        cout << query.ans << '\n';
    }
}