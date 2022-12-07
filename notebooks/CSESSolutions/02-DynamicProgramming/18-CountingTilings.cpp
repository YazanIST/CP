// Your task is to count the number of ways you can fill an n×m grid using 1×2 and 2×1 tiles.
int main() {
    int n, m;
    cin >> n >> m;
 
    vector<vector<int>> dp((1 << n), vector<int>(m, -1));
 
    auto isValidMask = [&](int mask) {
        for (int i = 10; i >= 1; i--) {
            if (!((1 << i) & mask)) continue;
            if ((1 << (i - 1)) & mask) {
                mask ^= (1 << i);
                mask ^= (1 << (i - 1));
                i--;
            }
        }
        return !mask;
    };
 
    vector<int> validMasks;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (isValidMask(mask)) {
            validMasks.push_back(mask);
        }
    }
    
    auto isValidNext = [&](int prev, int next) {
        for (int i = n - 1; i >= 0; i--) {
            if (((1 << i) & prev)) continue;
            if (((1 << i) & next)) {
                return -1;
            } else {
                next ^= (1 << i);
            }
        }
        return next;
    };
 
    function<int(int, int)> calc = [&](int prevMask, int index) -> int {
        if (index == m) {
            return prevMask == ((1 << n) - 1);
        }
 
        auto &ret = dp[prevMask][index];
        if (ret != -1) {
            return ret;
        }
 
        ret = 0;
 
        for (auto nextMask: validMasks) {
            int actualNext = isValidNext(prevMask, nextMask);
            if (actualNext != -1) {
                ret = add(ret, calc(actualNext, index + 1));
            }
        }
 
        return ret;
    };
 
    cout << calc((1 << n) - 1, 0);
}