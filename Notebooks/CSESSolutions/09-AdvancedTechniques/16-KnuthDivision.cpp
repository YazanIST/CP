// Given an array of n numbers, your task is to divide it into n subarrays, each of which has a single element.
// On each move, you may choose any subarray and split it into two subarrays. The cost of such a move is the sum of values in the chosen subarray.
// What is the minimum total cost if you act optimally?
int main(){
    int n;
    cin >> n;
 
    vector<ll> a(n);
    for (auto &x: a) cin >> x;
 
    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    vector<vector<int>> opt(n, vector<int>(n));
    vector<ll> pref(a);
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }
 
    function<ll(int, int)> getSum=[&](int l, int r)->ll {
        return pref[r] - (l ? pref[l - 1] : 0);
    };
 
    for (int l = n - 1; l >= 0; l--) {
        dp[l][l] = 0;
        opt[l][l] = l;
        for (int r = l + 1; r < n; r++) {
            for (int mid = opt[l][r - 1]; mid <= min(r - 1, opt[l + 1][r]); mid++) {
                if (dp[l][mid] + dp[mid + 1][r] + getSum(l, mid) + getSum(mid + 1, r) < dp[l][r]) {
                    opt[l][r] = mid;
                }
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r] + getSum(l, mid) + getSum(mid + 1, r));
            }
        }
    }
 
    cout << dp[0][n - 1];
}