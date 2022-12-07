// Given an array of n integers, your task is to count the number of subarrays having sum x.
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