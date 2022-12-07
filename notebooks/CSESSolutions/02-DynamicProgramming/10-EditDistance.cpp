// The edit distance between two strings is the minimum number of operations required to transform one string into the other.
// The allowed operations are:
// Add one character to the string.
// Remove one character from the string.
// Replace one character in the string.
// For example, the edit distance between LOVE and MOVIE is 2, because you can first replace L with M, and then add I.
// Your task is to calculate the edit distance between two strings.
int solve(int i, int j) {
    if (j == m) return n - i;
    if (i == n) return m - j;
    auto &cur = dp[i][j];
    if (cur != -1) return cur;
    if (a[i] == b[j]) return cur = solve(i + 1, j + 1); // take
    cur = solve(i + 1, j + 1) + 1;        // change
    cur = min(cur, solve(i, j + 1) + 1);  // add
    cur = min(cur, solve(i + 1, j) + 1);  // remove
    return cur;
}
void letsHopeItsRight() {
    cin >> a >> b;
    n = a.size();
    m = b.size();
    if (n > m) {
        swap(a, b);
        swap(n, m);
    }
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0);
}