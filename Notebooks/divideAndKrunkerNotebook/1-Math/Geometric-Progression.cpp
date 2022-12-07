ld geometricProgressionSum(ld r, ld n) {
    // first n terms a ^ 0 (1) + a ^ 1 + a ^ 2 .. a ^ (n - 1)
    if (abs(r - 1) <= EPS) {
        return n;
    }
    return (1 - powl(r, n)) / (1 - r);
}

ll geometricProgressionSum(ll r, ll n) {
    // first n terms a ^ 0 (1) + a ^ 1 + a ^ 2 .. a ^ (n - 1)
    if (r == 1) {
        return n;
    }
    return divide(sub(1, power(r, n)), sub(1, r));
}