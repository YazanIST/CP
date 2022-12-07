// Consider a money system consisting of n coins. Each coin has a positive integer value. Your task is to produce a sum of money x using the available coins in such a way that the number of coins is minimal.
const int INF = 1e9
int main() {
    int n, money;
    cin >> n >> money;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<int> dp(money + 1, INF);
    dp[money] = 0;
    for (int i = money - 1; i >= 0; i--) {
        for (auto x : a) {
            if (i + x <= money) {
                dp[i] = min(dp[i], dp[i + x] + 1);
            }
        }
    }
    replace(dp.begin(), dp.end(), INF, -1);
    cout << dp[0];
}