// Given an integer, your task is to find the number, sum and product of its divisors. As an example, let us consider the number 12:
// the number of divisors is 6 (they are 1, 2, 3, 4, 6, 12)
// the sum of divisors is 1+2+3+4+6+12=28
// the product of divisors is 1⋅2⋅3⋅4⋅6⋅12=1728
// Since the input number may be large, it is given as a prime factorization.
ll p[100001], k[100001];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i] >> k[i];
    ll div_cnt = 1, div_sum = 1, div_prod = 1, div_cnt2 = 1;
    for (int i = 0; i < n; i++)
    {
        div_cnt = div_cnt * (k[i] + 1) % MOD;
        div_sum = div_sum * (power(p[i], k[i] + 1) - 1) % MOD * power(p[i] - 1, MOD - 2) % MOD;
        div_prod = power(div_prod, k[i] + 1) * power(power(p[i], (k[i] * (k[i] + 1) / 2)), div_cnt2) % MOD;
        div_cnt2 = div_cnt2 * (k[i] + 1) % (MOD - 1);
    }
    cout << div_cnt << ' ' << div_sum << ' ' << div_prod;
    return 0;
}