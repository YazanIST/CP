// You are given a list consisting of n integers. Your task is to remove elements from the list at given positions, and report the removed elements.
void build(int p, int l, int r) {
    if (l == r) {
        seg[p] = 1;
        return;
    }
    int mid = l + (r - l) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    seg[p] = seg[p * 2] + seg[p * 2 + 1];
}
int getIndex(int p, int l, int r, int index) {
    if (l == r) {
        seg[p] = 0;
        return l;
    }
    int mid = l + (r - l) / 2, ret;
    if (index <= seg[p * 2]) {
        ret = getIndex(p * 2, l, mid, index);
    } else {
        ret = getIndex(p * 2 + 1, mid + 1, r, index - seg[p * 2]);
    }
    seg[p] = seg[p * 2] + seg[p * 2 + 1];
    return ret;
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 0, n - 1);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        cout << a[getIndex(1, 0, n - 1, x)] << ' ';
    }
}