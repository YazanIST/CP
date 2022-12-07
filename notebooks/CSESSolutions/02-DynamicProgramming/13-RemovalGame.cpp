// There is a list of n numbers and two players who move alternately. On each move, a player removes either the first or last number from the list, and their score increases by that number. Both players try to maximize their scores.
// What is the maximum possible score for the first player when both players play optimally?
const int N = 5001;
int n;
int x[N];
ll dp[N][N];
int main() {
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < n; i++)
        cin >> x[i], sum += x[i];
    for (int l = n - 1; l >= 0; l--) {
        for (int r = l; r < n; r++) {
            dp[l][r] = max(x[l] - dp[l + 1][r], x[r] - dp[l][r - 1]);
        }
    }
    cout << (sum + dp[0][n - 1]) / 2;
}