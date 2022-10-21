// find two integers such that their
// greatest common divisor is as large as possible
int main() {
    int n;
    cin >> n;
    vector<int> freq(MAX);
    while (n--) {
        int x;
        cin >> x;
        freq[x]++;
    }
    for (int i = MAX - 1; i > 0; i--) {
        int count = 0;
        for (int j = i; j < MAX; j += i) {
            count += freq[j];
        }
        if (count >= 2) {
            cout << i;
            return 0;
        }
    }
}