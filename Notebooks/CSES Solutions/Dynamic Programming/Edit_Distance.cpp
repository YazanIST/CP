// Add one, Remove one, Replace one
// The edit distance between two strings is
// the minimum number of operations required to
// transform one string into the other.
int solve(int i, int j) {
    if (j == m)
        return n - i;
    if (i == n)
        return m - j;
    auto &cur = dp[i][j];
    if (cur != -1)
        return cur;
    if (a[i] == b[j])
        return cur = solve(i + 1, j + 1); // take
    cur = solve(i + 1, j + 1) + 1;        // change
    cur = min(cur, solve(i, j + 1) + 1);  // add
    cur = min(cur, solve(i + 1, j) + 1);  // remove
    return cur;
}