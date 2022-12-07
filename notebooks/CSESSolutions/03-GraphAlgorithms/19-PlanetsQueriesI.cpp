// You are playing a game consisting of n planets. Each planet has a teleporter to another planet (or the planet itself).
// Your task is to process q queries of the form: when you begin on planet x and travel through k teleporters, which planet will you reach?
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> up[i][0];
        up[i][0]--;
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((1 << i) & k) {
                x = up[x][i];
            }
        }
        cout << x + 1 << '\n';
    }
}