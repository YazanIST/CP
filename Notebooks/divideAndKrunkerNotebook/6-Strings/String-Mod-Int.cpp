ll mod(string num, ll a) {
    ll ret = 0;
    for (ll i = 0; i < num.length(); i++)
        ret = (ret * 10 + (ll)num[i] - '0') % a;
    return ret;
}