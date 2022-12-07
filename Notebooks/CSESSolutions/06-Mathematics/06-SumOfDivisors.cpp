// Let σ(n) denote the sum of divisors of an integer n. For example, σ(12)=1+2+3+4+6+12=28.
// Your task is to calculate the sum ∑ni=1σ(i) modulo 109+7.
const int MOD = 1e9 + 7;
__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }
 
void solve() {
  __int128 n = read();
 
  auto getSum = [&](__int128 x) {
    return x * (x + 1) / 2;
  };
 
  __int128 curBlock = 1;
  __int128 sum = 0;
  while (curBlock <= n) {
    __int128 freq = n / curBlock;
    __int128 nextStart = n / freq + 1;
    nextStart = min(nextStart * 1LL, n + 1);
    if (nextStart > n) {
      sum += (getSum(n) - getSum(curBlock - 1) + MOD) % MOD;
      sum %= MOD;
      break;
    }
    __int128 secondTerm = getSum(nextStart - 1);
    __int128 firstTerm = getSum(curBlock - 1);
    // cout << curBlock << ' ' << nextStart << ' ' << secondTerm << ' ' << firstTerm << ' ';
    // cout << (secondTerm - firstTerm) * freq << '\n';
    sum += ((secondTerm - firstTerm) + MOD % MOD) * freq % MOD;
    sum %= MOD;
    curBlock = nextStart;
  }
  print(sum);
}