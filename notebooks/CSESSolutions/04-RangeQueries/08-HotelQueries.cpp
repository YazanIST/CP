// There are n hotels on a street. For each hotel you know the number of free rooms. Your task is to assign hotel rooms for groups of tourists. All members of a group want to stay in the same hotel.
// The groups will come to you one after another, and you know for each group the number of rooms it requires. You always assign a group to the first hotel having enough rooms. After this, the number of free rooms in the hotel decreases.
void build(int p, int l, int r) {
    if (l == r) {
        seg[p] = v[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
}
int get(int p, int l, int r, int x) {
    if (l == r) {
        if (seg[p] < x)
            return 0;
        return l + 1;
    }
    int mid = l + (r - l) / 2;
    if (seg[p * 2] >= x)
        return get(p * 2, l, mid, x);
    else
        return get(p * 2 + 1, mid + 1, r, x);
}
void update(int p, int l, int r, int idx, int x) {
    if (l == r) {
        v[l] -= x;
        seg[p] = v[l];
        return;
    }
    int mid = l + (r - l) / 2;
    if (idx <= mid)
        update(p * 2, l, mid, idx, x);
    else
        update(p * 2 + 1, mid + 1, r, idx, x);
    seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> v[i];
    build(1, 0, n - 1);
    while (m--) {
        int x;
        cin >> x;
        int ans = get(1, 0, n - 1, x);
        if (ans)
            update(1, 0, n - 1, ans - 1, x);
        cout << ans << ' ';
    }
}