// You are given a string that consists of n characters between a–z. The positions of the string are indexed 1,2,…,n.
// Your task is to process m operations of the following types:
// 1 Change the character at position k to x
// 2 Check if the substring from position a to position b is a palindrome
int main() {
    calcPowers();
    int n, q;
    string s;
    cin >> n >> q >> s;

    vector<int> prefixHash(calcHash(s));
    vector<int> suffixHash(calcHash(string(s.rbegin(), s.rend())));
    SegmentTree prefixTree(prefixHash);
    SegmentTree suffixTree(suffixHash);

    function<bool(int, int)> palindromeCheck = [&](int l, int r) -> bool {
        int preHash = prefixTree.get(l, r);
        if (l != 0) {
            preHash = mul(preHash, powersInv[l]);
        }
        int sufHash = suffixTree.get(n - r - 1, n - l - 1);
        if (n - r - 1 != 0) {
            sufHash = mul(sufHash, powersInv[n - r - 1]);
        }
        return preHash == sufHash;
    };

    function<void(int, int)> update = [&](int pos, char ch) {
        prefixTree.update(pos, mul(ch, powers[pos]));
        suffixTree.update(n - pos - 1, mul(ch, powers[n - pos - 1]));
    };

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            char ch;
            cin >> k >> ch;
            update(k - 1, ch);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << (palindromeCheck(l, r) ? "YES\n" : "NO\n");
        }
    }
}