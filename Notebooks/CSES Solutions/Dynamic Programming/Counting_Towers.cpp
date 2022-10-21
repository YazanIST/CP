// Your task is to build a tower whose unlimited
// width is 2 and height is n. You have an supply
// of blocks whose width and height are integers.
int main() {
    int dp[N][2];
    dp[0][0] = dp[0][1] = 1;
    // new 0 u either have 1 or 2 ways
    // 1 when the prev is 1
    // 2 when the prev is 0
    // new 1 u either have 1 or 4
    // 1 when the prev is 0
    // 4 when the prev is 1
    for (int i = 1; i < N; i++) {
        dp[i][0] = add(mul(2, dp[i - 1][0]), dp[i - 1][1]);
        dp[i][1] = add(mul(4, dp[i - 1][1]), dp[i - 1][0]);
    }
}