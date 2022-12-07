// The Hamming distance between two strings a and b of equal length is the number of positions where the strings differ.
// You are given n bit strings, each of length k and your task is to calculate the minimum Hamming distance between two strings.
int to_int(string s) {
    int ret = 0;
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); i++)
        ret |= ((s[i] - '0') << i);
    return ret;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i] = to_int(s);
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            ans = min(ans, __builtin_popcount(v[i] ^ v[j]));
    cout << ans;
}