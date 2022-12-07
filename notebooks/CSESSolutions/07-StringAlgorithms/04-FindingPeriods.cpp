// A period of a string is a prefix that can be used to generate the whole string by repeating the prefix. The last repetition may be partial. For example, the periods of abcabca are abc, abcabc and abcabca.
// Your task is to find all period lengths of a string.
int main(){
    calcPowers(); 
    string s;
    cin >> s;
    int n = s.size();
    vector<int> hash(calcHash(s));
    for (int len = 1; len <= n; len++) {
        bool good = true;
        for (int i = len; i < n; i += len) {
            int l = i, r = min(i + len - 1, n - 1);
            int curLen = r - l + 1;
            int substring = getHash(hash, l, r);
            int pattern = getHash(hash, 0, curLen - 1);
            if (pattern != substring) {
                good = false;
                break;
            }
        }
        if (good) {
            cout << len << ' ';
        }
    }
}