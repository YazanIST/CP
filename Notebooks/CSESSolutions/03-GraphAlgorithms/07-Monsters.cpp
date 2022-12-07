// You and some monsters are in a labyrinth. When taking a step to some direction in the labyrinth, each monster may simultaneously take one as well. Your goal is to reach one of the boundary squares without ever sharing a square with a monster.
// Your task is to find out if your goal is possible, and if it is, print a path that you can follow. Your plan has to work in any situation; even if the monsters know your path beforehand.
int const N = 1e3 + 1;
int n, m, Ax, Ay;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
string ds = "RLDU";
vector<vector<char>> grid(N, vector<char>(N));
vector<vector<int>> dis1(N, vector<int>(N, 1e9)), dis2(N, vector<int>(N, 1e9));
vector<vector<bool>> vis(N, vector<bool>(N));
vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(N));

bool valid(int i, int j) {
    return i >= 0 && j >= 0 && i < n && j < m;
}

bool isopenboarder(int i, int j) {
    return ((grid[i][j] == '.' || grid[i][j] == 'A') && (i == 0 || j == 0 || i == n - 1 || j == m - 1));
}

bool isopenboarder(pair<int, int> x) {
    return ((grid[x.first][x.second] == '.' || grid[x.first][x.second] == 'A') && (x.first == 0 || x.second == 0 || x.first == n - 1 || x.second == m - 1));
}

string followpath(pair<int, int> cur, pair<int, int> A) {
    string ans = "";
    while (cur != A) {
        if (parent[cur.first][cur.second].first == cur.first - 1) ans += 'D';
        else if (parent[cur.first][cur.second].first == cur.first + 1) ans += 'U';
        else if (parent[cur.first][cur.second].second == cur.second - 1) ans += 'R';
        else ans += 'L';
        cur = parent[cur.first][cur.second];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void bfs1() {
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                q.push({i, j});
                vis[i][j] = true;
                dis1[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int di = cur.first + dx[i];
            int dj = cur.second + dy[i];
            if (valid(di, dj) && !vis[di][dj] && grid[di][dj] != '#') {
                vis[di][dj] = true;
                dis1[di][dj] = dis1[cur.first][cur.second] + 1;
                q.push({di, dj});
            }
        }
    }
}

void bfs2(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    vis[x][y] = true;
    dis2[x][y] = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        if (isopenboarder(cur)) {
            string ans = followpath(cur, {x, y});
            cout << "YES\n" << ans.size() << '\n' << ans;
            exit(0);
        }
        for (int i = 0; i < 4; i++) {
            int di = cur.first + dx[i];
            int dj = cur.second + dy[i];
            if (!valid(di, dj) || vis[di][dj]) continue;
            if (grid[di][dj] == '#') continue;
            vis[di][dj] = true;
            dis2[di][dj] = dis2[cur.first][cur.second] + 1;
            parent[di][dj] = {cur.first, cur.second};
            if (dis2[di][dj] >= dis1[di][dj]) continue;
            q.push({di, dj});
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    bfs1();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            vis[i][j] = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'A')
                bfs2(i, j);
    cout << "NO";
}