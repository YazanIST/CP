// report, after each change, the length of the longest substring whose each bit is the same.
template <int bit>
struct Node {
    int curBit;
    int length, bestPrefix, bestSuffix, ans;
    Node(int x = (!bit)) {
        curBit = x;
        bestSuffix = bestPrefix = ans = (x == bit);
        length = 1;
    }
    Node(const Node &lhs, const Node &rhs) {
        curBit = -1;
        length = lhs.length + rhs.length;
        bestPrefix = lhs.bestPrefix;
        if (lhs.bestPrefix == lhs.length) {
            bestPrefix += rhs.bestPrefix;
        }
        bestSuffix = rhs.bestSuffix;
        if (rhs.bestSuffix == rhs.length) {
            bestSuffix += lhs.bestSuffix;
        }
        ans = max({lhs.ans, rhs.ans, lhs.bestSuffix + rhs.bestPrefix});
    }
};
int main() {
    int q;
    string s;
    cin >> s >> q;
    vector<bool> init;
    for (auto ch : s)
        init.push_back(ch - '0');
    SegmentTree<Node<0>> zeros(init);
    SegmentTree<Node<1>> ones(init);
    while (q--) {
        int index;
        cin >> index;
        zeros.update(index - 1);
        ones.update(index - 1);
        cout << max(zeros.getAns(), ones.getAns()) << ' ';
    }
}