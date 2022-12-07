// Consider a money system consisting of n coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ways you can produce a money sum x using the available coins.
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<int> dp(x + 1);
    dp[0] = 1;
    for (int i = 1; i <= x; i++)
        for (int j = 0; j < n; j++)
            if (i - a[j] >= 0)
                dp[i] = add(dp[i], dp[i - a[j]]);
    cout << dp[x];
}