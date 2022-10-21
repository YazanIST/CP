void solve() {
    ll a, b;
    cin >> b >> a;
    if (a > b) {
        if (a % 2) cout << a * a - b + 1;
        else a--, cout << a * a + b;
    }
    else {
        if (b % 2) b--, cout << b * b + a;
        else cout << b * b - a + 1;
    }
    cout << '\n';
}