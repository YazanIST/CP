#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

// All functions assume given numbers are already under MOD
// if not, you might need to add mod function to get all numbers under mod

const int MOD = 1e9 + 7;

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
    while (p > 0) {
        if (p % 2) 
            ret = mul(ret, x);
        p /= 2;
        x = mul(x, x);
    }
    return ret;
}

int inv(int x) {
    return power(x, MOD - 2);
}

inline int divide(int a, int b) {
    return mul(a, inv(b));
}

int fact(int x) {
    if (x <= 1) {
        return 1;
    }

    return mul(x, fact(x - 1));
}

int nPr(int n, int r) {
    return divide(fact(n), fact(n - r));
}

int nCr(int n, int r) {
    return divide(fact(n), mul(fact(n - r), fact(r)));
}