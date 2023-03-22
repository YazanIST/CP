#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int MOD1 = 1e9 + 7, PRIME1 = 31;
const int MOD2 = 1e9 + 9, PRIME2 = 37;
vector<int> powersMOD1, powersInvMOD1;
vector<int> powersMOD2, powersInvMOD2;

inline int add(int a, int b, int mod) {
    return (a + b) % mod;
}

inline int sub(int a, int b, int mod) {
    return (a - b + mod) % mod;
}

inline int mul(int a, int b, int mod) {
    return (ll) a * b % mod;
}

int power(int x, int p, int mod) {
    int ret = 1;
    while (p) {
        if (p%2) {
            ret = mul(ret, x, mod);
        }
        p /= 2;
        x = mul(x, x, mod);
    }
    return ret;
}

int inv(int x, int mod) {
    return power(x, mod - 2, mod);
}

int divide(int a, int b, int mod) {
    return mul(a, inv(b, mod), mod);
}

void calcPowers() {
    powersMOD1.push_back(1);
    powersMOD2.push_back(1);
    for (int i = 0; i < N; i++) {
        powersMOD1.push_back(mul(powersMOD1.back(), PRIME1, MOD1));
        powersMOD2.push_back(mul(powersMOD2.back(), PRIME2, MOD2));
    }
    for (auto x: powersMOD1) {
        powersInvMOD1.push_back(inv(x, MOD1));
    }
    for (auto x: powersMOD2) {
        powersInvMOD2.push_back(inv(x, MOD2));
    }
}

vector<pair<int,int>> calcHash(const string&s) {
    vector<pair<int, int>> ret(s.size());
    for (int i = 0; i < (int) s.size(); i++) {
        if (i > 0) {
            ret[i] = ret[i - 1];
        }
        ret[i].first = add(ret[i].first, mul(s[i], powersMOD1[i], MOD1), MOD1);
        ret[i].second = add(ret[i].second, mul(s[i], powersMOD2[i], MOD2), MOD2);
    }
    return ret;
} 

pair<int,int> getHash(const vector<pair<int, int>> &hash, int l, int r) {
    if (l == 0) {
        return hash[r];
    }
    pair<int, int> ret;
    ret.first = mul(sub(hash[r].first, hash[l - 1].first, MOD1), powersInvMOD1[l], MOD1);
    ret.second = mul(sub(hash[r].second, hash[l - 1].second, MOD2), powersInvMOD2[l], MOD2);
    return ret;
}
