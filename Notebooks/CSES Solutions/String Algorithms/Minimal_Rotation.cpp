// A rotation of a string can be generated by moving characters one after
// another from beginning to end. For example,
// the rotations of acab are acab, caba, abac, and baca.
// Your task is to determine the lexicographically minimal rotation of a string.
int main() {
    calcPowers();
    string s;
    cin >> s;
    int n = s.size();
    s += s;
    vector<int> sHash(calcHash(s));
    int ans = 0;
    function<int(int)> getLCPLen = [&](int i) -> int {
        if (s[ans] != s[i])
        {
            return 0;
        }
        int l = 0, r = n - 1, ret = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (getSubHash(sHash, i, i + mid) == getSubHash(sHash, ans, ans + mid))
            {
                ret = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ret + 1;
    };
    for (int i = 1; i < n; i++)
    {
        int lcpLength = getLCPLen(i);
        if (lcpLength == n)
        {
            continue;
        }
        if (s[i + lcpLength] < s[ans + lcpLength])
        {
            ans = i;
        }
    }
    cout << s.substr(ans, n);
}