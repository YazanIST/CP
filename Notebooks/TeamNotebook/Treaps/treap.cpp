// Given a string, your task is to process operations where you
// cut a substring and paste it to the end of the string.
// What is the final string after all the operations?
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using TreapType = char;
 
struct Node {
  Node *left, *right;
  int weight, size;
  TreapType value;
  Node(TreapType v) {
    left = right = NULL;
    weight = rng();
    size = 1;
    value = v;
  }
};
 
int size(Node *treap) {
  if (treap == NULL) return 0;
  return treap->size;
}
 
void merge(Node *&treap, Node *left, Node *right) {
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
    Node *left, *middle;
    split(root, left, middle, l);
    Node *right;
    split(middle, middle, right, r - l + 1);
    merge(root, right, middle);
    merge(root, left, root);
  }
  cout << root << '\n';
  return 0;
}