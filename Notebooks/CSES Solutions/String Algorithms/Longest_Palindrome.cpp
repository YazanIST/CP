// Given a string, your task is to determine the
// longest palindromic substring of the string.
// For example, the longest palindrome in aybabtu is bab.
int main()
{
    calcPowers();
    string s;
    cin >> s;
    int n = s.size();
    vector<int> prefHash(calcHash(s));
    vector<int> suffHash(calcHash(string(s.rbegin(), s.rend())));
    function<bool(int, int, int, int)> check2Parts = [&](int l0, int r0, int l1, int r1) -> bool {
        return getHash(prefHash, l0, r0) == getHash(suffHash, n - r1 - 1, n - l1 - 1);
    };
    function<int(int)> checkOdd = [&](int midPoint) -> int {
        int length = min(midPoint, n - midPoint - 1);
        if (!length) {
            return 1;
        }
        int l = 1, r = length, ret = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check2Parts((midPoint - 1) - (mid - 1), midPoint - 1, midPoint + 1, (midPoint + 1) + (mid - 1))) {
                ret = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ret * 2 + 1;
    };
    function<int(int)> checkEven = [&](int midPoint) -> int {
        int length = min(midPoint, n - midPoint);
        if (!length) {
            return 0;
        }
        if (s[midPoint] != s[midPoint - 1]) {
            return 0;
        }
        int l = 0, r = length - 1, ret = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check2Parts(midPoint - 1 - mid, midPoint - 1, midPoint, midPoint + mid)) {
                ret = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return (ret + 1) * 2;
    };
    int ansLen = 1, ansIndex = 0;
    for (int i = 0; i < n; i++) {
        int odd = checkOdd(i);
        int even = checkEven(i);
        if (odd > ansLen) {
            ansLen = odd;
            ansIndex = i - ansLen / 2;
        }
        if (even > ansLen) {
            ansLen = even;
            ansIndex = i - ansLen / 2;
        }
    }
    cout << s.substr(ansIndex, ansLen);
}