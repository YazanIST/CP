// Consider an infinite string
// 12345678910111213141516171819202122232425...
// what is the digit at position k in the string?
const int N = 15;
int vis[N + 5][N + 5];
string s;
void solve() {
    cin >> s;
    int ans = 0;
    auto check = [&](int i, int j) { 
        return i > 0 && j > 0 && j <= 7 && i <= 7 && !vis[i][j];
    };
    auto one = [&](int i, int j) { 
        int ret = check(i - 1, j) + check(i + 1, j) + check(i, j - 1) + check(i, j + 1);    
        if (i == 7 && j == 1)
            return 0;
        return int(ret == 1);
    };
    vi di {-1, 1, 0, 0}, dj {0, 0, -1, 1};
    string dd = "UDLR";
    function<void(int, int, int)> dfs = [&](int i, int j, int c) {
        if ((i == 7 && j == 1)) {
            if (c == 48)
                ans++;
            return;
        }
        int ud = check(i - 1, j) + check(i + 1, j) , lr = check(i, j - 1) + check(i, j + 1);
        if ((ud == 2 && !lr) || (!ud && lr == 2))
            return;
        vis[i][j] = 1;
        ++c;
        for(int d = 0; d < 4; ++d) {
            int ti = di[d] + i, tj = dj[d] + j;
            if(one(ti, tj) && check(ti, tj)) {
                if((dd[d] == s[c - 1]) || s[c - 1] == '?')
                    dfs(ti, tj, c);
                vis[i][j] = 0;
                return;
            }
        }
        for(int d = 0; d < 4; ++d) {
            int ti = di[d] + i, tj = dj[d] + j;
            if(check(ti, tj)) {
                if((dd[d] == s[c - 1]) || s[c - 1] == '?')
                    dfs(ti, tj, c);
            }
        }
        vis[i][j] = 0;
    };
    dfs(1, 1, 0);
    cout << ans;
}