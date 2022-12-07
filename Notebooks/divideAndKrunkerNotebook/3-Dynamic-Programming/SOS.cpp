// SOS
const int BITS = 20;
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> dp(1 << BITS, 0); // dp[x] = how many ys are subsets of x (x | y = x)
    for (int x : a) {
        ++dp[x];
    }
    for (int i = 0; i < BITS; ++i) {
        for (int mask = 0; mask < (1 << BITS); ++mask)
        {
            if ((mask & (1 << i)) != 0)
            {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
    vector<int> dp2(1 << BITS, 0); // dp2[x] = how many ys are supersets of x (x & y = x)
    for (int x : a) {
        ++dp2[x];
    }
    for (int i = 0; i < BITS; ++i) {
        for (int mask = (1 << BITS) - 1; mask >= 0; --mask) {
            if ((mask & (1 << i)) == 0) {
                dp2[mask] += dp2[mask ^ (1 << i)];
            }
        }
    }
    for (int x : a) {
        int xComp = x ^ ((1 << BITS) - 1); // dp[xComp] = how many ys such that y &x = 0
        cout << dp[x] << ’ ’ << dp2[x] << ’ ’ << n - dp[xComp] << ’\n’;
    }
}