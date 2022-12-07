// You are given an array that contains each number between 1…n exactly once. Your task is to collect the numbers from 1 to n in increasing order.
// On each round, you go through the array from left to right and collect as many numbers as possible. What will be the total number of rounds?
void lets_hope_its_right() {
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].first, v[i].second = i;
    sort(v.begin(), v.end());
    int ans = 1;
    for (int i = 1; i < n; i++)
        if (v[i].second < v[i - 1].second)
            ans++;
    cout << ans;
}