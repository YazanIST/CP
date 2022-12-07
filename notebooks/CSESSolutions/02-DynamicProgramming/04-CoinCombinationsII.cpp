// Consider a money system consisting of n coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ordered ways you can produce a money sum x using the available coins.
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    int dp[x + 1] = {1};
    for (int i = 0; i < n; i++) {
        for (int sum = 1; sum <= x; sum++) {
            if (sum - a[i] >= 0) {
                dp[sum] = add(dp[sum], dp[sum - a[i]]);
            }
        }
    }
    cout << dp[x];
}