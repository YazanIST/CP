// Your task is to count the number of ways you can
// fill an n×m grid using 1×2 and 2×1 tiles.
const int MOD = 1e9 + 7;
inline int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }
inline bool isSet(int mask, int bit) { return ((mask >> bit) & 1) != 0; }
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> nextStates(1 << n);
  auto generateNextStates = [&](int mask) {
    vector<bool> marked(n);
    int notMask = ~mask & ((1 << n) - 1);
    function<void(int)> helper = [&](int index) {
      if (index == n) {
        int nextMask = notMask;
        for (int i = 0; i < n; ++i) {
          if (marked[i]) {
            nextMask |= 1 << i;
          }
        }
        nextStates[mask].push_back(nextMask);
        return;
      }
      if (index != n - 1 && !isSet(notMask, index) && !isSet(notMask, index + 1)) {
        marked[index] = marked[index + 1] = true;
        helper(index + 2);
        marked[index] = marked[index + 1] = false;
      }
      helper(index + 1);
    };
    helper(0);
  };
  for (int mask = 0; mask < (1 << n); ++mask) {
    generateNextStates(mask);
  }
  vector<int> dp(1 << n);
  dp[(1 << n) - 1] = 1;
  for (int i = 0; i < m; ++i) {
    vector<int> newDp(1 << n);
    for (int mask = 0; mask < (1 << n); ++mask) {
      for (int nextMask : nextStates[mask]) {
        newDp[nextMask] = add(newDp[nextMask], dp[mask]);
      }
    }
    dp = newDp;
  }
  cout << dp[(1 << n) - 1] << '\n';
  return 0;
}