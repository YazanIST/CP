struct Node {
    Node *l, *r;
    int sum;
    Node(int x) : l(nullptr), r(nullptr), sum(x) {}
    Node(Node *l, Node *r) : l(l), r(r), sum(0) {
        if (l != nullptr) sum += l->sum;
        if (r != nullptr) sum += r->sum;
    }
};
Node *build(int s, int e) {
    if (s == e) {
        return new Node(0);
    }
    int mid = (s + e) / 2;
    return new Node(build(s, mid), build(mid + 1, e));
}
Node *update(Node *node, int s, int e, int idx) {
    if (s == e) {
        return new Node(node->sum + 1);
    }
    int mid = (s + e) / 2;
    if (idx <= mid) return new Node(update(node->l, s, mid, idx), node->r);
    else return new Node(node->l, update(node->r, mid + 1, e, idx));
}
int get(Node *node, int s, int e, int l, int r) {
    if (l > e || s > r) {
        return 0;
    }
    if (l <= s && e <= r) {
        return node->sum;
    }
    int mid = (s + e) / 2;
    return get(node->l, s, mid, l, r) + get(node->r, mid + 1, e, l, r);
}