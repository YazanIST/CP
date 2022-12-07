vector<ll> PrimeFactorization(ll x) {
    vector<ll> primes;
    while (x % 2 == 0) {
        primes.push_back(2);
        x /= 2;
    }

    for (ll i = 3; i * i <= x; i += 2) {
        while (x % i == 0) {
            primes.push_back(i);
            x /= i;
        }
    }

    if (x > 2) primes.push_back(x);
    return primes;
}