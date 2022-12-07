// Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, every second child is removed from the circle, until there are no children left.
// Your task is to process q queries of the form: "when there are n children, who is the kth child that will be removed?"
int go(int n, int k, int parity) {
    if (2 * k + parity <= n) {
        return 2 * k + parity;
    }
    int removed = (n + 2 - parity) / 2;
    if ((n + 1) % 2 == 0) {
        return (parity ^ 1) | (go(n - removed, k - removed, parity) << 1);
    } else {
        return (parity ^ 1) | (go(n - removed, k - removed, parity ^ 1) << 1);
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    int ans = go(n - 1, k - 1, 1) + 1;
    cout << ans << '\n';
}