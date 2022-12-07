class Solution {
public:
    int maxCoins(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int> (n));
    for (int l = n - 1; l >= 0; --l) {
        for (int r = l; r < n; ++r) {
            for (int last = l; last <= r; ++last) {
                dp[l][r] = max(
                    dp[l][r],
                    a[last] * (l - 1 >= 0 ? a[l - 1] : 1) * (r + 1 < n ? a[r + 1] : 1)
                + (last - 1 >= l ? dp[l][last - 1] : 0) + (last + 1 <= r ? dp[last + 1][r] : 0)
                );
            }
        }
    }
    return dp[0][n - 1];
    }
};
Footer
