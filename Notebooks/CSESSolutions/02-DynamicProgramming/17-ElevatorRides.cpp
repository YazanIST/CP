// There are n people who want to get to the top of a building which has only one elevator. You know the weight of each person and the maximum allowed weight in the elevator. What is the minimum number of elevator rides?
int main(){
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (auto &x: w) cin >> x;
    vector<pair<int,int>> dp((1 << n), {n + 1, 0}); // first -> rides, second -> max weight
    dp[0] = {1, 0};
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((1 << i) & mask) {
                auto last = dp[mask ^ (1 << i)];
                if (last.second + w[i] <= x) {
                    last.second += w[i];
                } else {
                    last.first++;
                    last.second = w[i];
                }
                dp[mask] = min(dp[mask], last);
            }
        }
    }
    cout << dp[(1 << n) - 1].first;
}