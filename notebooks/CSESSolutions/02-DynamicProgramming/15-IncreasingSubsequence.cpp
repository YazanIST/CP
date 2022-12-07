// You are given an array containing n integers. Your task is to determine the longest increasing subsequence in the array, i.e., the longest subsequence where every element is larger than the previous one.
int lis(vector<int> const &a) {
    int n = a.size();
    vector<int> dp(n + 1, INF);
    dp[0] = -INF;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[j - 1] < a[i] && a[i] < dp[j]) dp[j] = a[i];
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)
        if (dp[i] < INF)
            ans = i;
    return ans;
}