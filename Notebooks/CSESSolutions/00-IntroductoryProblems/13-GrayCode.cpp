// A Gray code is a list of all 2n bit strings of length n, where any two successive strings differ in exactly one bit (i.e., their Hamming distance is one).
// Your task is to create a Gray code for a given length n.
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = n - 1; j >= 0; j--)
            cout << bool((1 << j) & (i ^ (i >> 1)));
        cout << '\n';
    }
}