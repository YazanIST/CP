// There are n cities and m flight connections between them.
// You want to travel from Syrjälä to Lehmälä so that you
// visit each city exactly once. How many possible routes are there?
const int N = 20;
vector<int> g[N];
int dp[1 << N][N], n, m;

int solve(int mask, int node) {
  if (mask == (1 << n) - 1) return 1;
  int &ret = dp[mask][node];
  if (ret != -1) return ret;
  ret = 0;
  for (int to : g[node]) {
    if (((1 << to) & mask) != 0) continue;
    if (to == n - 1 && (mask | (1 << to)) != ((1 << n) - 1)) continue;
    ret = add(ret, solve(mask | (1 << to), to));
  }
  return ret;
};
 
int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
  }
  memset(dp, -1, sizeof(dp));
  int ans = solve(1, 0);
  cout << ans << '\n';
  return 0;
}