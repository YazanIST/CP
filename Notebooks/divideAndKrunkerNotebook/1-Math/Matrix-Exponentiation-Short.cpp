using Matrix = vector<vector<ll>>;
Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  Matrix ret(n + 1, vector<ll>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= n; ++k) {
        ret[i][j] = (ret[i][j] + lhs[i][k] * rhs[k][j] % MOD) % MOD;
      }
    }
  }
  return ret;
}
 
Matrix matPow(Matrix base, ll p) {
  Matrix ret(n + 1, vector<ll> (n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      ret[i][j] = (i == j);
    }
  }
  while (p) {
    if (p % 2 == 1) {
      ret = ret * base;
    }
    base = base * base;
    p >>= 1;
  }
  return ret;
}