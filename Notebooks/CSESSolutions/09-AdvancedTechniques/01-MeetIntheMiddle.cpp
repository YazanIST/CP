// You are given an array of n numbers. In how many ways can you choose a subset of the numbers with sum x?
vector<ll> partSums[2];
void generateSubsetsSums(int l, int r, ll sum, const vector<int> &v, const int part) {
    if (l == r) {
        partSums[part].push_back(sum);
        return;
    }
    generateSubsetsSums(l + 1, r, sum + v[l], v, part);
    generateSubsetsSums(l + 1, r, sum, v, part);
}
int main() {
    int n, target;
    cin >> n >> target;
    vector<int> t(n);
    for (auto &x : t) cin >> x;
    sort(t.begin(), t.end());
    int mid = n / 2;
    generateSubsetsSums(0, mid, 0, t, 0);
    generateSubsetsSums(mid, n, 0, t, 1);
    sort(partSums[1].begin(), partSums[1].end());
    ll ans = 0;
    for (auto x : partSums[0]) {
        ll serachFor = target - x;
        auto ub = upper_bound(partSums[1].begin(), partSums[1].end(), serachFor);
        auto lb = lower_bound(partSums[1].begin(), partSums[1].end(), serachFor);
        ans += ub - lb;
    }
    cout << ans;
}