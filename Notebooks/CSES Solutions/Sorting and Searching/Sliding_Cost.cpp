// calculate for each window of k elements, from left to right,
// the minimum total cost of making all elements equal.
// u can increase or decrease each element with cost x where
// x is the difference between the new and the original value.
// The total cost is the sum of such costs.
int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n), compressed, mapped;
    Fenwick<ll> ft(n);
    for (auto &x : a) cin >> x;
    compressed = compress(a);
    for (int i = 0; i < n; i++) {
        int value = a[i];
        int newValue = lower_bound(compressed.begin(),
                compressed.end(), value) - compressed.begin();
        mapped.push_back(newValue);
    }
    for (int i = 0; i < k; i++) {
        update(1, 0, n - 1, mapped[i], 1);
        ft.add(mapped[i], a[i]);
    }
    for (int i = 0; i <= n - k; i++) {
        ll ans = 0;
        int medianIndex = get(1, 0, n - 1, (k - 1) / 2);
        int median = compressed[medianIndex];
        ans += getSum(1, 0, n - 1, 0, medianIndex - 1) * (ll)median - ft.sum(0, medianIndex - 1);
        ans += ft.sum(medianIndex + 1, n - 1) -
                getSum(1, 0, n - 1, medianIndex + 1, n - 1) * (ll)median;
        cout << ans << ' ';
        if (i < n - k) {
            update(1, 0, n - 1, mapped[i], -1);
            update(1, 0, n - 1, mapped[i + k], 1);
            ft.add(mapped[i], -a[i]);
            ft.add(mapped[i + k], a[i + k]);
        }
    }
}