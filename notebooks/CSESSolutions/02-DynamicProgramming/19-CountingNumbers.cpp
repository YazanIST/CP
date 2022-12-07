// Your task is to count the number of integers between a and b where no two adjacent digits are the same.
inline bool isGood(int n) {
    string s = to_string(n);
    for (int i = 1; i < (int) s.size(); i++) {
        if (s[i] == s[i - 1]) {
            return false;
        }
    }
    return true;
}
int main(){
    ll l, r;
    cin >> l >> r;
    vector<vector<vector<vector<ll>>>> dp;
    function<ll(int, int, bool, bool, const string&)> calc = [&](int pos, int lastDig, bool leadingZeros, bool isLower, const string &bound)->ll {
        if (pos == (int) bound.size()) {
            return isLower;
        }
 
        auto &ret = dp[pos][lastDig][leadingZeros][isLower];
        if (ret != -1) {
            return ret;
        }
 
        ret = 0;
        for (int next = 0; next < 10; next++) {
            if (next == lastDig) continue;
            if (next == 0 && leadingZeros) {
                ret += calc(pos + 1, 10, true, true, bound);
                continue;
            }
            if (next > (bound[pos] - '0') && isLower) {
                ret += calc(pos + 1, next, false, true, bound);
            } else if (next <= (bound[pos] - '0')) {
                ret += calc(pos + 1, next, false, isLower || (next < (bound[pos] - '0')), bound);
            }
        }
 
        return ret;
    };
    dp = vector<vector<vector<vector<ll>>>> (19, vector<vector<vector<ll>>>(11, vector<vector<ll>>(2, vector<ll>(2, -1))));
    ll calcR = (r > 1 ? calc(0, 10, true, false, to_string(r)) + isGood(r) : r + 1);
    dp = vector<vector<vector<vector<ll>>>> (19, vector<vector<vector<ll>>>(11, vector<vector<ll>>(2, vector<ll>(2, -1))));
    ll calcL = (l > 1 ? (calc(0, 10, true, false, to_string(l - 1)) + isGood(l - 1)) :  l);
    cout << calcR - calcL;
}