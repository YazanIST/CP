// Given an array of n integers, you have to process following operations:
// 1 reverse a subarray
// 2 calculate the sum of values in a subarray
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using TreapType = int;
 
struct Node {
    Node *left, *right;
    int weight, size;
    bool pending;
    TreapType value;
    ll sum;
    Node(TreapType v) {
        left = right = NULL;
        weight = rng();
        size = 1;
        value = sum = v;
        pending = false;
    }
};
 
void prop(Node *node) {
    if (!node) {
        return;
    }
 
    if (node -> pending) {
        swap(node->left, node->right);
        node->pending = false;
        if (node->left) {
            node->left->pending = !node->left->pending;
        }
        if (node->right) {
            node->right->pending = !node->right->pending;
        }
    }
}
 
int size(Node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}
 
int getValue(Node *treap) {
    return treap? treap->value: 0;
}
 
ll getSum(Node *treap) {
    return treap? treap->sum: 0;
}
 
void pull(Node *treap) {
    if (!treap) {
        return;
    }
    prop(treap);
    treap->size = size(treap->left) + size(treap->right) + 1;
    treap->sum = getSum(treap->left) + getSum(treap->right) + getValue(treap);
}
 
void merge(Node *&treap, Node *left, Node *right) {
    prop(treap);
    prop(left);
    prop(right);
    if (left == NULL) treap = right;
    else if(right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }
        pull(treap);
    }
}
 
Node *createTreap(const vector<TreapType> &v) {
    Node *treap = NULL;
    for (auto x : v) {
        merge(treap, treap, new Node(x));
    }
    return treap;
}
 
void split(Node *treap, Node *&left, Node *&right, int k) {
    prop(treap);
    prop(left);
    prop(right);
    if (treap == NULL) {
        left = right = NULL;
    } else {
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k-size(treap->left)-1);
            left = treap;
        } else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        pull(treap);
    }
}
 
template<class E>
void processSubarray(Node *&treap, int l, int r, const E &fun) {
    Node *left = NULL, *middle = NULL, *right = NULL;
    split(treap, left, middle, l);
    split(middle, middle, right, r - l + 1);
    fun(middle);
    merge(treap, left, middle);
    merge(treap, treap, right);
}
 
void reverse(Node *&treap, int l, int r) {
    processSubarray(treap, l, r, [&](Node *middle) {
        if (middle) {
            middle->pending = !middle->pending;
        }
    });
}
 
ll getSubsum(Node *&treap, int l, int r) {
    ll ans = 0;
    processSubarray(treap, l, r, [&](Node *middle) {
        ans = getSum(middle);
    });
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
 
    Node* treap = createTreap(a);
 
    while (m--) {
        int type, l, r;
        cin >> type >> l >> r;
        l--, r--;
        if (type == 1) {
            reverse(treap, l, r);
        } else {
            cout << getSubsum(treap, l, r) << '\n';
        }
    }
}