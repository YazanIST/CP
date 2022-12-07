// Given an array of n positive integers, your task is to count the number of subarrays having sum x.
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) cin >> v[i];
    int l = 0, r = 0, ans = 0;
    ll sum = v[0];
    while (r < n) {
        if (sum > x) {
            sum -= v[l];
            l++;
            if (l >= r && l < n) {
                sum = v[l];
                r = l;
            } else if (l >= n) break;
        } else if (sum < x) {
            r++;
            if (r < n) sum += v[r];
            else break;
        } else {
            ans++;
            r++;
            if (r < n) sum += v[r];
            else break;
        }
    }
    cout << ans;
}