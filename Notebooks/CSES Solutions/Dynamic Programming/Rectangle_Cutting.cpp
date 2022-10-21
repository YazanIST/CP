// Given an a×b rectangle, your task is to cut it into squares. On each move you
// can select a rectangle and cut it into two rectangles in such a way that all side
// lengths remain integers. What is the minimum possible number of moves?
// 1 ≤ a, b ≤ 500
int main() {
    int a, b;
    cin >> a >> b;
    int dp[a + 1][b + 1];
    for (int i = 0; i <= a; i++)
        for (int j = 0; j <= b; j++)
            dp[i][j] = ((i == j || !i || !j) ? 0 : INF);
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j)
                continue;
            for (int k = 1; k <= i; k++) {
                dp[i][j] = min(dp[i][j], dp[i - k][j] + dp[k][j] + 1);
            }
            for (int k = 1; k <= j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][j - k] + dp[i][k] + 1);
            }
        }
    }
    cout << dp[a][b];
}