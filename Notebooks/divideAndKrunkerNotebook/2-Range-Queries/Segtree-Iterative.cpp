class IterativeSegmentTree {
public:
    IterativeSegmentTree() {}
    
    IterativeSegmentTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size, NEUTRAL);
        for (int i = 0; i < n; ++i) tree[i + size] = 0;
        for (int i = size - 1; i > 0; --i) pull(i);
    }
 
    inline void operator=(const IterativeSegmentTree &other) {
        tree = other.tree;
        n = other.n;
        size = other.size;
    }
 
    void update(int i, int v) {
        i += size;
        tree[i] = v;
        while (i > 1) {
            i /= 2;
            pull(i);
        }
    }
 
    int get(int l, int r) {
        int leftRes(NEUTRAL);
        int rightRes(NEUTRAL);
        for (l += size, r += size; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) leftRes = combine(leftRes, tree[l++]);
            if (r % 2 == 0) rightRes = combine(tree[r--], rightRes);
        }
        return combine(leftRes, rightRes);
    }
 
private:
    vector<int> tree;
    int n, size;
    const int NEUTRAL = 0; // edit here
 
    void pull(int i) { tree[i] = combine(tree[2 * i], tree[2 * i + 1]); }
 
    int combine(int lhs, int rhs) { return max(lhs, rhs); } // edit here
};

template <typename T, class F>
class segtree {
 public:
  segtree() = default;
  segtree(int n, const F &combine, const T &neutral) : segtree(std::vector<T>(n, neutral), combine, neutral) {}
  segtree(const std::vector<T> &v, const F &combine, const T &neutral) : n(v.size()), combine(combine), NEUTRAL(neutral) {
    size = 1;
    while (size < n) size *= 2;
    tree.resize(2 * size, NEUTRAL);
    for (int i = 0; i < n; ++i) tree[i + size] = v[i];
    for (int i = size - 1; i > 0; --i) pull(i);
  }

  void set(int i, T v) {
    i += size;
    tree[i] = v;
    while (i > 1) {
      i /= 2;
      pull(i);
    }
  }

  T get(int i) { return tree[i + size]; }

  T prod(int l, int r) {
    T leftRes(NEUTRAL);
    T rightRes(NEUTRAL);
    for (l += size, r += size; l <= r; l /= 2, r /= 2) {
      if (l % 2 == 1) leftRes = combine(leftRes, tree[l++]);
      if (r % 2 == 0) rightRes = combine(tree[r--], rightRes);
    }
    return combine(leftRes, rightRes);
  }

  T allProd() { return tree[1]; }

  template <class E> int minLeft(int r, const E &can) {
    assert(can(NEUTRAL));
    T acc(NEUTRAL);
    r += size;
    while (true) {
      while (r > 1 && r % 2 == 1) r /= 2;
      if (T tmp = combine(tree[r], acc); can(tmp)) {
        if ((r & (r - 1)) == 0) break;
        acc = tmp;
        --r;
      } else {
        while (r < size) {
          if (T tmp = combine(tree[2 * r + 1], acc); can(tmp)) {
            acc = tmp;
            r = 2 * r;
          } else {
            r = 2 * r + 1;
          }
        }
        return r + 1 - size;
      }
    }
    return 0;
  }

  template <class E> int maxRight(int l, const E &can)  {
    assert(can(NEUTRAL));
    T acc(NEUTRAL);
    l += size;
    while (true) {
      while (l % 2 == 0) l /= 2;
      if (T tmp = combine(acc, tree[l]); can(tmp)) {
        if ((l & (l + 1)) == 0) break;
        acc = tmp;
        ++l;
      } else {
        while (l < size) {
          if (T tmp = combine(acc, tree[2 * l]); can(tmp)) {
            acc = tmp;
            l = 2 * l + 1;
          } else {
            l = 2 * l;
          }
        }
        return l - 1 - size;
      }
    }
    return n - 1;
  }

 private:
  std::vector<T> tree;
  int n, size;
  F combine;
  const T NEUTRAL;

  void pull(int i) { tree[i] = combine(tree[2 * i], tree[2 * i + 1]); }
};