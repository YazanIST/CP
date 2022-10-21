// calculate the median of each window
// of k elements, from left to right
void solve() { // segtree functions
    int n, k;
    cin >> n >> k;
    vector<int> a(n), compressed, mapped;
    for (int i = 0; i < n; i++) cin >> a[i];
    compressed = compress(a);
    for (int i = 0; i < n; i++) {
        int value = a[i];
        int newValue = lower_bound(compressed.begin(),
                compressed.end(), value) - compressed.begin();
        mapped.push_back(newValue);
    }
    for (int i = 0; i < k; i++)
        update(1, 0, n - 1, mapped[i], 1);
    for (int i = 0; i <= n - k; i++) {
        cout << compressed[get(1, 0, n - 1, (k - 1) / 2)] << ' ';
        update(1, 0, n - 1, mapped[i], -1);
        update(1, 0, n - 1, mapped[i + k], 1);
    }
}