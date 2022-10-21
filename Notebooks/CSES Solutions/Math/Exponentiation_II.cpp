// calculate values a^b^c modulo 1e9+7
int r = power(b, c, MOD - 1);
cout << power(a, r, MOD) << '\n';