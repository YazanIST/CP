// You are given a string that consists of n characters between a–z.
// The positions of the string are indexed 1,2,…,n.
// Your task is to process m operations of the following types:
// Change the character at position k to x
// Check if the substring from position a to position b is a palindrome
// DONT ACCUMULATE the hash
int main() {
    calcPowers();
    int n, q;
    string s;
    cin >> n >> q >> s;
    pair<vector<int>, vector<int>> Hash = calcHash(s);
    SegmentTree frontSeg(Hash.first), backSeg(Hash.second);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx;
            char ch;
            cin >> idx >> ch;
            frontSeg.update(idx, mul(powers[idx - 1], ch - 'a' + 1));
            backSeg.update(n - idx + 1, mul(powers[n - idx], ch - 'a' + 1));
        } else {
            int l, r;
            cin >> l >> r;
            int frontHash = sub(frontSeg.get(0, r), frontSeg.get(0, l - 1));
            frontHash = mul(frontHash, powersInverse[l - 1]);
            int backHash = sub(backSeg.get(0, n - l + 1), backSeg.get(0, n - r));
            backHash = mul(backHash, powersInverse[n - r]);
            cout << ((frontHash == backHash) ? "YES\n" : "NO\n");
        }
    }
}