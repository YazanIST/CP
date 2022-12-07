// There is a bit string consisting of n bits. Then, there are some changes that invert one given bit. Your task is to report, after each change, the length of the longest substring whose each bit is the same.
template <class Node>
class SegmentTree {
private:
    int n;
    Node seg[N * 4];
    void build(int p, int l, int r, const vector<bool> &init) {
        if (l == r) {
            seg[p] = Node(init[l]);
            return;
        }
        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, init);
        build(p * 2 + 1, mid + 1, r, init);
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }

    void update(int p, int l, int r, int index) {
        if (l == r) {
            seg[p] = Node(!seg[p].curBit);
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            update(p * 2, l, mid, index);
        } else {
            update(p * 2 + 1, mid + 1, r, index);
        }
        seg[p] = Node(seg[p * 2], seg[p * 2 + 1]);
    }
public:
    SegmentTree(const vector<bool> &init) {
        n = init.size();
        build(1, 0, n - 1, init);
    }
    void update(int index) {
        update(1, 0, n - 1, index);
    }
    ll getAns() {
        return seg[1].ans;
    }
};
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
    for (auto ch : s) init.push_back(ch - '0');
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
