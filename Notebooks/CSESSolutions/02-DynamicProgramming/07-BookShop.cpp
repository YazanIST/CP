// You are in a book shop which sells n different books. You know the price and number of pages of each book.
// You have decided that the total price of your purchases will be at most x. What is the maximum number of pages you can buy? You can buy each book at most once.
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (auto &x : h) cin >> x;
    for (auto &x : s) cin >> x;
    vector<int> dp(x + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> curDp(x + 1);
        for (int j = 1; j <= x; j++) {
            curDp[j] = max(curDp[j], dp[j]);
            if (j - h[i - 1] >= 0)
                curDp[j] = max(curDp[j], dp[j - h[i - 1]] + s[i - 1]);
        }
        dp = curDp;
    }
    cout << dp[x];
}