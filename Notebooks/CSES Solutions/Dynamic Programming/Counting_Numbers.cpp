// Your task is to count the number of integers between
// a and b where no two adjacent digits are the same.
const int DIGITS = 10;
 
inline int toDigit(char c) {
  return c - '0';
}

i64 solve(i64 x) {
  if (x < 0) return 0;
  if (x == 0) return 1;
  
  string s = to_string(x);
  int n = s.size();
 
  vector<array<i64, 2>> dp(DIGITS);
  for (int digit = 1; digit < toDigit(s[0]); ++digit) {
    ++dp[digit][0];
  }
  ++dp[toDigit(s[0])][1];
 
  for (int index = 1; index < n; ++index) {
    vector<array<i64, 2>> newDp(DIGITS);
    for (int lastDigit = 0; lastDigit < DIGITS; ++lastDigit) {
      for (int newDigit = 0; newDigit < DIGITS; ++newDigit) {
        if (lastDigit == newDigit) {
          continue;
        }
        newDp[newDigit][0] += dp[lastDigit][0];
        if (newDigit < toDigit(s[index])) {
          newDp[newDigit][0] += dp[lastDigit][1];
        } else if (newDigit == toDigit(s[index])) {
          newDp[newDigit][1] += dp[lastDigit][1];
        }
      }
    }
    for (int digit = 1; digit < DIGITS; ++digit) {
      ++newDp[digit][0];
    }
    dp = newDp;
  }
 
  i64 ret = 1;
  for (int digit = 0; digit < DIGITS; ++digit) {
    ret += dp[digit][0];
    ret += dp[digit][1];
  }
  return ret;
}
int main() {
  i64 a, b;
  cin >> a >> b;
  i64 ans = solve(b) - solve(a - 1);
  cout << ans << '\n';
  return 0;
}