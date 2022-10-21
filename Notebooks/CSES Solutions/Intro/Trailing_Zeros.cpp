// calculate the number of trailing
// zeros in the factorial n!.
void solve() {
    int base = 5, ans = 0, n;
    cin >> n;
    while (base <= n) {
        ans += n / base;
        base *= 5;
    }
    cout << ans;
}