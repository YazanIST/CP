// Gray Code equation
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = n - 1; j >= 0; j--)
            cout << bool((1 << j) & (i ^ (i >> 1)));
        cout << '\n';
    }
}