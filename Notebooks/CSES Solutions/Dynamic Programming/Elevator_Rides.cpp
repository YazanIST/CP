// There are n people who want to get to the top of a building
// which has only one elevator. You know the weight of each
// person and the maximum allowed weight in the elevator.
// What is the minimum number of elevator rides?
const int N = 1 << 20;
int n, x, a[N];
pair<int, int> dp[N];
int main() {
  cin >> n >> x;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i < (1 << n); ++i) {
    dp[i] = {20, 0};
  }
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if (~i & (1 << j)) {
        int to = i ^ (1 << j);
        pair<int, int> nxt;
        if (a[j] + dp[i].second > x) {
          nxt = {1 + dp[i].first, min(a[j], dp[i].second)};
        } else {
          nxt = {dp[i].first, a[j] + dp[i].second};
        }
        dp[to] = min(dp[to], nxt);
      }
    }
  }
  int ones = (1 << n) - 1;
  int ans = dp[ones].first + min(dp[ones].second, 1);
  cout << ans << '\n';
  return 0;
}