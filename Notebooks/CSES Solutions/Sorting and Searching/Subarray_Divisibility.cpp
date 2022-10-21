// count the number of subarrays where
// the sum of values is divisible by n.
// 1 ≤ n ≤ 2e5
// −1e9 ≤ ai ≤ 1e9
void solve() {
    int n;
    cin >> n;
    vector<ll> m(n);
    m[0] = 1;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
        m[(sum % n + n) % n]++;
    }
    ll ans = 0;
    for (auto x : m)
        ans += x * (x - 1) / 2;
    cout << ans;
}