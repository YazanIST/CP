const int N = 2e6 + 5;

int spf[N];
int mob[N];
int phi[N];

void sieve() {
  for (int i = 2; i < N; i += 2) {
    spf[i] = 2;
  }
  
  for (int i = 3; i < N; i += 2) {
    spf[i] = i;
  }

  for (int i = 3; i * i < N; i += 2) {
    if (spf[i] == i) {
      for (int j = i * i; j < N; j += (i << 1)) {
        spf[j] = i;
      }
    } 
  }
}

bool isPrime(int n) {
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

void mobius() {
  for (int i = 1; i < N; ++i) {
    mob[i] = 1;
  }
  for (int i = 2; i < N; ++i) {
    if (isPrime(i)) {
      mob[i] = -1;
      for (int j = 2 * i; j < N; j += i) {
        mob[j] = (j % (i * i) == 0) ? 0 : -mob[j];
      }
    }
  }
}

void totient() {
  for (int i = 0; i < N; i++)
    phi[i] = i;

  for (int i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (int j = i; j < N; j += i) {
        phi[j] -= phi[j] / i;
      }
    }
  }
}

int getUpTo(int n) {
  int ind = n;
  for (int i = 2; i * i <= n; ++i) {
    ind += mob[i] * n / (i * i);
  }
  return ind;
}

vector<int> dp(N);
int calcDepth(int x) {
  if (x <= 1) return 0;
  if (dp[x] != 0) return dp[x];
  return dp[x] = calcDepth(phi[x]) + 1;
}

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> div(n + 1);
  for (int i = 2; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      div[j].push_back(i);
    }
  }
  for (int i = 2; i <= n; ++i) {
    cout << i << '\n';
    for (auto x : div[i]) {
      cout << x << ' ';
    }
    cout << '\n';
  }
}