ll findSqrt(ll x) {
    ll l = 1, r = 1e9;
    ll ret = 1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (mid * mid == x) {
            return mid;
        }
        if (mid * mid > x) {
            r = mid - 1;
        } else {
            ret = mid;
            l = mid + 1;
        }
    }
    return ret;
}