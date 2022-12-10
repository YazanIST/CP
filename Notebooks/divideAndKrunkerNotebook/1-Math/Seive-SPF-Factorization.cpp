// Factorizing in log(n)
const int N = 10;
int spf[N];

void sieve() {
    for (int i = 2; i < N; i += 2) spf[i] = 2;
    for (int i = 3; i < N; i += 2) spf[i] = i;
    for (int i = 3; i * i < N; i += 2) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += (i << 1)) spf[j] = i;
        }
    }
}

bool isprime(int n) {
    return (n == spf[n]);
}

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> ret;
    while (n != 1) {
        int cnt = 0;
        int x = spf[n];
        while (n % x == 0) {
            ++cnt;
            n /= x;
        }
        ret.emplace_back(x, cnt);
    }
    return ret;
}
