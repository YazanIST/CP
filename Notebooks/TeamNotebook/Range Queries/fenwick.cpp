template <typename T>
class Fenwick {
private:
    vector<T> fen;
    int n;

public:
    explicit Fenwick(int n) : n(n) { fen.assign(n, T(0)); }
    
    void add(int at, T by) {
        for (++at; at <= n; at += at & -at) {
            fen[at - 1] += by;
        }
    }

    T sum(int at) {
        T ret = T(0);
        for (++at; at > 0; at -= at & -at) {
            ret += fen[at - 1];
        }
        return ret;
    }
    
    T sum(int l, int r) {
        T ret = sum(r);
        if (l != 0) {
            ret -= sum(l - 1);
        }
        return ret;
    }
};