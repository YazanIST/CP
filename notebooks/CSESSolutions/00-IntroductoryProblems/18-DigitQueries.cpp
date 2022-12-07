// Consider an infinite string that consists of all positive integers in increasing order:
// 12345678910111213141516171819202122232425...
// Your task is to process q queries of the form: what is the digit at position k in the string?
void solve() {
    ll k;
    cin >> k;
    ll prev = 0, cur = 10, idx = 9, sz = 1, lastidx = 0;
    if(k <= 9) {
        cout << k << '\n';
        return;
    }
    while(idx < k) {
        sz += 1;
        prev = cur;
        cur  = cur * 10;
        lastidx = idx;
        idx += (cur - prev) * sz;
    }
    ll l = prev, r = cur - 1, ans = 0;
    while(l <= r) {
        ll mid = (r + l) / 2;
        if((mid - prev) * sz + (lastidx + 1) <= k) {
            if(mid > ans) ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    string temp = to_string(ans);
    ll need = k - ((ans - prev) * sz + (lastidx + 1));
    cout << temp[need] << '\n';
}