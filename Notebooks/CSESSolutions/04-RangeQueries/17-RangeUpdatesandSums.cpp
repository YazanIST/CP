// Your task is to maintain an array of n values and efficiently process the following types of queries:
// 1 Increase each value in range [a,b] by x.
// 2 Set each value in range [a,b] to x.
// 3 Calculate the sum of values in range [a,b].
struct Node {
    ll ans, lazyAdd, lazySet;
    Node() : ans(0), lazyAdd(0), lazySet(0) {}
};
const int N = 2e5 + 1;
int n, q, a[N];
Node seg[N * 4];
inline void propagate(int p, int l, int r) {
    if (seg[p].lazySet) {
        if (l != r) {
            seg[p * 2].lazySet = seg[p].lazySet;
            seg[p * 2 + 1].lazySet = seg[p].lazySet;
            seg[p * 2].lazyAdd = 0;
            seg[p * 2 + 1].lazyAdd = 0;
        }
        seg[p].ans = seg[p].lazySet * (r - l + 1);
        seg[p].lazySet = 0;
    }
    if (seg[p].lazyAdd) {
        if (l != r) {
            seg[p * 2].lazyAdd += seg[p].lazyAdd;
            seg[p * 2 + 1].lazyAdd += seg[p].lazyAdd;
        }
        seg[p].ans += seg[p].lazyAdd * (r - l + 1);
        seg[p].lazyAdd = 0;
    }
}
inline void combine(int p) {
    seg[p].ans = seg[p * 2].ans + seg[p * 2 + 1].ans;
}
void build(int p, int l, int r) {
    if (l == r) {
        seg[p].ans = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    combine(p);
}
ll get(int p, int l, int r, int a, int b) {
    propagate(p, l, r);
    if (a <= l && r <= b)
        return seg[p].ans;
    if (r < a || l > b)
        return 0;
    int mid = l + (r - l) / 2;
    return get(p * 2, l, mid, a, b) + get(p * 2 + 1, mid + 1, r, a, b);
}
void update(int p, int l, int r, int a, int b, int value, bool type) {
    propagate(p, l, r);
    if (a <= l && r <= b) {
        if (type) {
            seg[p].lazyAdd = 0;
            seg[p].lazySet = value;
        } else {
            if (seg[p].lazySet) {
                seg[p].lazySet += value;
            } else {
                seg[p].lazyAdd += value;
            }
        }
        propagate(p, l, r);
        return;
    }
    if (r < a || l > b) return;
    int mid = l + (r - l) / 2;
    update(p * 2, l, mid, a, b, value, type);
    update(p * 2 + 1, mid + 1, r, a, b, value, type);
    combine(p);
}