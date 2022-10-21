// count the number of subarrays having sum x
// 1 ≤ n ≤ 2e5
// −1e9 ≤ x , ai ≤ 1e9
void solve() {
    int n, x;
    cin >> n >> x;
    map<ll, int> mp;
    mp[0] = 1;
    ll presum = 0, ans = 0;
    while (n--) {
        int X;
        cin >> X;
        presum += X;
        ans += mp[presum - x];
        mp[presum]++;
    }
    cout << ans;
}