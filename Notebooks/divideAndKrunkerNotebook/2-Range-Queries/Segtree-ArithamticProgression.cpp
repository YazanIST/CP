struct Node {
    ll a, d, sum;
    Node() {
        a = d = sum = 0;
    }
    Node(ll x) {
        a = d = 0;
        sum = x;
    }
    Node(ll _a, ll _d) {
        a = _a;
        d = _d;
        sum = 0;
    }
    ll getSum(ll len) const {
        return (a * 2 + (len - 1) * d) * len / 2;
    }
    ll move(ll len) const {
        return (a + (len - 1) * d);
    }
};
Node combine(const Node &l, const Node &r) {
    return l.sum + r.sum;
}
inline void push(int p, int s, int e) {
    if (seg[p].a == 0) return;
    seg[p].sum += seg[p].getSum(e - s + 1);
    if (e != s) {
        seg[p << 1].a += seg[p].a;
        seg[p << 1].d += seg[p].d;
        seg[p << 1 | 1].a += seg[p].move((e + s) / 2 + 1 - s + 1);
        seg[p << 1 | 1].d += seg[p].d;
    }
    seg[p].a = seg[p].d = 0;
}
void update(int p, int s, int e, int l, int r, const Node &x) {
    push(p, s, e);
    if (e < l || s > r) {
        return;
    }
    if (l <= s && e <= r) {
        seg[p].a += x.move(s - l + 1);
        seg[p].d += x.d;
        push(p, s, e);
        return;
    }
    int m = (s + e) >> 1;
    update(p << 1, s, m, l, r, x);
    update(p << 1 | 1, m + 1, e, l, r, x);
    seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
}