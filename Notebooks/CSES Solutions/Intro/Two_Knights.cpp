// Your task is to count for k=1,2,…,n the number of
// ways two knights can be placed on a k×k chessboard
// so that they do not attack each other.
int main() {
    int n;
    cin >> n;
    cout << "0\n";
    ll dis = 0, add = 4;
    for (ll i = 2; i <= n; i++) {
        ll all = i * i * (i * i - 1) / 2;
        cout << all - 2 * dis << '\n';
        dis += add;
        add += 4;
    }
}