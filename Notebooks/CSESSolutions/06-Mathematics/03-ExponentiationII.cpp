// Your task is to efficiently calculate values a^(b^c) modulo 10^9+7.
int r = power(b, c, MOD - 1);
cout << power(a, r, MOD) << '\n';