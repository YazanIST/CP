// There are 88418 paths in a 7×7 grid from the upper-left square to the lower-left square. Each path corresponds to a 48-character description consisting of characters D (down), U (up), L (left) and R (right).
// corresponds to the description DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD.
// You are given a description of a path which may also contain characters ? (any direction). Your task is to calculate the number of paths that match the description.
string s;
int ans = 0;
bool vis[7][7];
bool valid(int i, int j) {
    return i >= 0 && i < 7 && j >= 0 && j < 7 && !vis[i][j];
}
void dfs(int i, int j, int steps) {
    if (i == 6 && j == 0) {
        if (steps == 48)
            ans++;
        else
            return;
    }
    if(!valid(i - 1,j) && !valid(i+1,j) && valid(i,j+1) && valid(i,j-1)) return;
    if(valid(i - 1,j) && valid(i+1,j) && !valid(i,j+1) && !valid(i,j-1)) return;
    vis[i][j] = 1;
    if (s[steps] == 'L' || s[steps] == '?') {
        if (j && !vis[i][j-1])
            dfs(i, j - 1, steps + 1);
    }
    if (s[steps] == 'R' || s[steps] == '?') {
        if (j < 6 && !vis[i][j+1])
            dfs(i, j + 1, steps + 1);
    }
    if (s[steps] == 'U' || s[steps] == '?') {
        if (i && !vis[i-1][j])
            dfs(i - 1, j, steps + 1);
    }
    if (s[steps] == 'D' || s[steps] == '?') {
        if (i<6 && !vis[i+1][j])
            dfs(i + 1, j, steps + 1);
    }
    vis[i][j] = 0;
}
int main() {
    cin >> s;
    dfs(0, 0, 0);
    cout << ans;
}