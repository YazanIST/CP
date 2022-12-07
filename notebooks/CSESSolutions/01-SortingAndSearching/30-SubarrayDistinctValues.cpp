// Given an array of n integers, your task is to calculate the number of subarrays that have at most k distinct values.
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    map<int, int> freq;
    int count = 0;
    auto add = [&](int x) {
        if (!freq[x]) {
            count++;
        }
        freq[x]++;
    };
    auto rem = [&](int x) {
        freq[x]--;
        if (!freq[x]) {
            count--;
        }
    };
    int l = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        add(a[i]);
        while (count > k) {
            rem(a[l++]);
        }
        ans += i - l + 1;
    }
    cout << ans;
}