class SegmentTree {
  private:
    struct Node {
      Node *lc;
      Node *rc;
      int val;
 
      Node() : lc(nullptr), rc(nullptr), val(0) {}
 
      static Node *getNode() {
        static Node nodes[70 * N];
        static Node *ret = nodes;
        return ret++;
      }
 
      void pull() {
        val = lc->val + rc->val;
      }
 
      void expand() {
        if (lc == nullptr) lc = getNode();
        if (rc == nullptr) rc = getNode();
      }
  
      ll sum(int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (ql <= l && r <= qr) return val;
        expand();
        int m = (r + l) / 2;
        return lc->sum(l, m, ql, qr) + rc->sum(m + 1, r, ql, qr);
      }
 
      void increase(int l, int r, int indx, int value) {
        if (l == r) {
          val += value;
          return;
        }
        expand();
        int m = (r + l) / 2;
        if (indx <= m) {
          lc->increase(l, m, indx, value);
        } else {
          rc->increase(m + 1, r, indx, value);
        }
        pull();
      }
    };
    int L, R;
    Node *root;
 
  public:
    SegmentTree(int l, int r) : L(l), R(r), root(new Node) {}
 
    ll sum (int l, int r) {
      return root->sum(L, R, l, r);
    }
    
    void increase(int indx, int value) {
      root->increase(L, R, indx, value);
    }
};