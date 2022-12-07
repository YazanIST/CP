// Your task is to build a tower whose width is 2 and height is n. You have an unlimited supply of blocks whose width and height are integers.
// Given n, how many different towers can you build? Mirrored and rotated towers are counted separately if they look different.
int main() {
    int dp[N][2];
    dp[0][0] = dp[0][1] = 1;
    for (int i = 1; i < N; i++) {
        dp[i][0] = add(mul(2, dp[i - 1][0]), dp[i - 1][1]);
        dp[i][1] = add(mul(4, dp[i - 1][1]), dp[i - 1][0]);
    }
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        n--;
        cout << add(dp[n][0], dp[n][1]) << '\n';
    }
}