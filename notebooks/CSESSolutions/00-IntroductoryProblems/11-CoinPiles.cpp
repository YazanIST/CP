// You have two coin piles containing a and b coins. On each move, you can either remove one coin from the left pile and two coins from the right pile, or two coins from the left pile and one coin from the right pile.
void solve() {
    int a, b;
    cin >> a >> b;
    if ((a + b) % 3 == 0 && min(a, b) * 2 >= max(a, b)) cout << "YES";
    else cout << "NO";
}