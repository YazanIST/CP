// Given a string, your task is to process operations
// where you reverse a substring of the string.
// What is the final string after all the operations?
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using TreapType = char;
 
struct Node {
  Node *left, *right;
  int weight, size;
  TreapType value;
  bool pending;
  Node(TreapType v) {
    left = right = NULL;
    weight = rng();
    size = 1;
    value = v;
    pending = false;
  }
};
 
void prop(Node *node) {
  if (!node) return;
  if (node->pending) {
    swap(node->left, node->right);
    if (node->left) {
      node->left->pending = !node->left->pending;
    }
    if (node->right) {
      node->right->pending = !node->right->pending;
    }
    node->pending = false;
  }
}
 
int size(Node *treap) {
  if (treap == NULL) return 0;
  return treap->size;
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
    treap->size = size(treap->left)+size(treap->right)+1;
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
    treap->size = size(treap->left)+size(treap->right)+1;
  }
}
 
void reverse(Node *&root, int l, int r) {
  Node *left = nullptr, *middle = nullptr, *right = nullptr;
  split(root, left, middle, l);
  split(middle, middle, right, r - l + 1);
  if (middle) {
    middle->pending = !middle->pending;
  }
  merge(root, left, middle);
  merge(root, root, right);
}
 
void insertAt(Node *&treap, Node *added, int pos) {
  assert(pos <= size(treap));
  Node *left = NULL;
  Node *right = NULL;
  split(treap, left, right, pos);
  merge(treap, left, added);
  merge(treap, treap, right);
}
 
Node *remove(Node *&treap, int l, int r) {
  Node *left = NULL, *middle = NULL, *right = NULL;
  split(treap, left, middle, l);
  split(middle, middle, right, r - l + 1);
  merge(treap, left, right);
  return middle;
}
 
ostream &operator<<(ostream &os, Node *treap) {
  prop(treap);
  if (!treap) return os;
  return os << treap->left << treap->value << treap->right;
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, q;
  cin >> n >> q;
  vector<char> s(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  Node *root = createTreap(s);
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    reverse(root, l, r);
  }
 
  cout << root << '\n';
  return 0;
}