void towerOfHanoi(int count, char n1, char n2, char n3) {
    if (count == 0) return;
    towerOfHanoi(count - 1, n1, n3, n2);
    cout << n1 << ' ' << n3 << '\n';
    towerOfHanoi(count - 1, n2, n1, n3);
}
int main() {
    int n;
    cin >> n;
    cout << (1 << n) - 1 << '\n';
    towerOfHanoi(n, '1', '2', '3');
}