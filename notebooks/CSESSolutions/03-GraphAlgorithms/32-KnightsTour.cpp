// Given a starting position of a knight on an 8×8 chessboard, your task is to find a sequence of moves such that it visits every square exactly once.
// On each move, the knight may either move two steps horizontally and one step vertically, or one step horizontally and two steps vertically.
// sort things to go to increasing by it's degree
int main() {
    int a, b;
    cin >> a >> b;
    a--, b--;
    swap(a, b);
    vector<vector<int>> grid(N, vector<int>(N, -1));
    auto isValid = [&](int i, int j) {
        return i >= 0 && j >= 0 && i < N && j < N;
    };
    auto getDeg = [&](int i, int j) {
        int ret = 0;
        for (int dir = 0; dir < 8; dir++) {
            int di = dx[dir] + i;
            int dj = dy[dir] + j;
            if (!isValid(di, dj)) continue;
            ret += (grid[di][dj] == -1);
        }
        return ret;
    };
    function<bool(int, int, int)> dfs = [&](int i, int j, int count) -> bool {
        grid[i][j] = count;
        if (count == 64) {
            return true;
        }
        vector<pair<int,pair<int,int>>> next;
        for (int dir = 0; dir < 8; dir++) {
            int di = dx[dir] + i;
            int dj = dy[dir] + j;
            if (!isValid(di, dj)) continue;
            if (grid[di][dj] != -1) continue;
            next.push_back({getDeg(di, dj), {di, dj}});
        }
        sort(next.begin(), next.end());
        for (auto [deg, nxt]: next) {
            auto [di, dj] = nxt;
            if (dfs(di, dj, count + 1)) {
                return true;
            }
        }
        grid[i][j] = -1;
        return false;
    };
    dfs(a, b, 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}