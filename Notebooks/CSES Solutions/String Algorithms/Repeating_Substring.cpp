// A repeating substring is a substring that occurs in two (or more) locations in the string.
// Your task is to find the longest repeating substring in a given string.
int main() {
    cin >> s;
    n = s.size();
    calcPowers();
    calcHashes();
    pair<int, int> ans = {0, 0};
    auto repetitionOfSizeK = [&](int k) {
        set<pair<int, int>> foundHashes;
        for (int i = 1; i + k - 1 <= n; i++) {
            pair<int, int> newHash{getHash1(i, i + k - 1), getHash2(i, i + k - 1)};
            if (foundHashes.count(newHash)) {
                return pair<int, int>{i - 1, k};
            } else {
                foundHashes.insert(newHash);
            }
        }
        return pair<int, int>{0, 0};
    };
    int l = 1, r = n;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        pair<int, int> cur = repetitionOfSizeK(mid);
        if (cur.second) {
            ans = cur;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << (ans.second ? s.substr(ans.first, ans.second) : "-1");
}