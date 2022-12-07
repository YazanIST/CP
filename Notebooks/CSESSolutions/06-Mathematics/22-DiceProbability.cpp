// You throw a dice n times, and every throw produces an outcome between 1 and 6. What is the probability that the sum of outcomes is between a and b?
const int N = 101;
int n, a, b;
double dp[N][N * N];
int main() {
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N * N; j++) {
            for (int k = 1; k <= 6; k++) {
                if (j - k >= 0) {
                    dp[i][j] += dp[i - 1][j - k] * (1.0 / 6);
                }
            }
        }
    }
    int n, a, b;
    cin >> n >> a >> b;
    double ans = 0;
    for (int i = a; i <= b; i++) {
        ans += dp[n][i];
    }
    cout << setprecision(6) << fixed << ans;
}