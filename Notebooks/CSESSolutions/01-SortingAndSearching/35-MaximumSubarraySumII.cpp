// Given an array of n integers, your task is to find the maximum sum of values in a contiguous subarray with length between a and b.
const ll INF = 1e18;
int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<ll> pref(n + 1);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }
    multiset<ll> mst;
    ll ans = -INF;
    for (int i = a; i <= n; i++) {
        if (mst.size() >= (b - a + 1))
            mst.erase(mst.find(pref[i - b - 1]));
        mst.insert(pref[i - a]);
        ans = max(ans, pref[i] - *mst.begin());
    }
    cout << ans;
}