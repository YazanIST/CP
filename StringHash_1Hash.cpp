const int N = 1e5 + 10;
const int MOD = 1e9 + 7, PRIME = 31;
vector<int> powers, powersInv;

inline int add(int a, int b) {
    return (a + b) % MOD;
}

inline int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

inline int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int power(int x, int p) {
    int ret = 1;
    while (p) {
        if (p % 2) {
            ret = mul(ret, x);
        }
        p /= 2;
        x = mul(x, x);
    }
    return ret;
}

int inv(int x) {
    return power(x, MOD - 2);
}

int divide(int a, int b) {
    return mul(a, inv(b));
}

void calcPowers(){
    powers.push_back(1);
    for (int i = 0; i < N; i++) {
        powers.push_back(mul(powers.back(), PRIME));
    }
    for (auto x:powers){
        powersInv.push_back(inv(x));
    }
}

vector<int> calcHash(const string &s) {
    vector<int>ret(s.size());
    for (int i = 0; i < (int) s.size(); i++) {
        if (i) {
            ret[i] = ret[i - 1];
        }
        ret[i] = add(ret[i], mul(s[i], powers[i]));
    }
    return ret;
}

int getHash(const vector<int> &hash, int l, int r){
    if (l == 0) {
        return hash[r];
    }
    return mul(sub(hash[r], hash[l - 1]), powersInv[l]);
}
