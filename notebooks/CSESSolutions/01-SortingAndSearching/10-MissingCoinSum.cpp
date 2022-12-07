// You have n coins with positive integer values. What is the smallest sum you cannot create using a subset of the coins?
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    ll sum = 1;
    sort(v.begin(), v.end());
    for (int i = 0; i < n && v[i] <= sum; i++) sum += v[i];
    cout << sum;
}