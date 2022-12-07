// In a movie festival, n movies will be shown. Syrjälä's movie club consists of k members, who will be all attending the festival.
// You know the starting and ending time of each movie. What is the maximum total number of movies the club members can watch entirely if they act optimally?
int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> movies(n);
    for (auto &[a, b] : movies) {
        cin >> b >> a;
    }
    sort(movies.begin(), movies.end());
    int ans = 0;
    multiset<int> mst;
    for (int i = 0; i < k; i++) mst.insert(0);
    for (auto [a, b] : movies) {
        auto it = mst.upper_bound(b);
        if (it == mst.begin())
            continue;
        --it;
        mst.erase(it);
        mst.insert(a);
        ans++;
    }
    cout << ans;
}