int main() {
    int n;
    cin >> n;
    double ans = 0;
    for(int i = n; i >= 1; i--) {
        ans += log10(i);
    }
    cout << "Number of digits of " << n << "! is " << floor(ans) + 1;
}