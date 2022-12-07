// Given an array of n integers, your task is to find the maximum sum of values in a contiguous, nonempty subarray.
int main() {
    int n;
    cin >> n;
    ll ans = -INF, sum = 0, mn = 0;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        sum += x;
        ans = max(ans, sum - mn);
        mn = min(mn, sum);
    }
    cout << ans;
}