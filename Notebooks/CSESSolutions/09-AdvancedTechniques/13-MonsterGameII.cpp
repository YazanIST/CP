// You are playing a game that consists of n levels. Each level has a monster. On levels 1,2,…,n−1, you can either kill or escape the monster. However, on level n you must kill the final monster to win the game.
// Killing a monster takes sf time where s is the monster's strength and f is your skill factor. After killing a monster, you get a new skill factor (lower skill factor is better). What is the minimum total time in which you can win the game?
template <typename T>
struct DynamicHull {
public:
    // Two operation types are supported:
    // - Insert a new line with slope equals to k and intercept equals to m.
    // - Given a param x, find the maximum value of k * x + m among lines_.
    //
    // Note:
    // If you want to eval in floating type, use a floating type instance directly.
    // The integral type instance may skip some lines
    // if they only dominate an interval that does not contain an integer.
 
    struct Line {
        static constexpr T inf = std::numeric_limits<T>::max();
        T k, m;
        mutable T p;
        Line(T k, T m, T p) : k(k), m(m), p(p) {}
        bool operator<(const Line &rhs) const {
            return k < rhs.k;
        }
        bool operator<(T query_p) const {
            return p < query_p;
        }
    };
 
    void insert_line(T k, T m) {
        auto y = lines_.insert(Line(k, m, 0));
        for (auto z = std::next(y); isect(y, z); z = lines_.erase(z));
        if (y != lines_.begin()) {
            auto x = std::prev(y);
            if (isect(x, y)) isect(x, y = lines_.erase(y));
            while ((y = x) != lines_.begin() && (--x)->p >= y->p) isect(x, lines_.erase(y));
        }
    }
 
    T eval(T x) const {
        auto line = *lines_.lower_bound(x);
        return line.k * x + line.m;
    }
 
    bool empty() const { return lines_.empty(); }
    int size() const { return lines_.size(); }
    const std::multiset<Line, std::less<>> &lines() const { return lines_; }
 
private:
    using iterator = typename std::multiset<Line>::iterator;
 
    T div(T a, T b) const {
        if constexpr (std::is_integral<T>::value) {
            return a / b - ((a ^ b) < 0 && a % b);
        } else {
            return a / b;
        }
    }
    bool isect(iterator a, iterator b) const {
        if (b == lines_.end()) {
            a->p = Line::inf;
            return false;
        }
        if (a->k == b->k) a->p = a->m > b->m ? Line::inf : -Line::inf;
        else a->p = div(b->m - a->m, a->k - b->k);
        return a->p >= b->p;
    }
 
    std::multiset<Line, std::less<>> lines_;
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int n, x;
    cin >> n >> x;
 
    vector<int> s(n), f(n);
    for (auto &x: s) cin >> x;
    for (auto &x: f) cin >> x;
 
    DynamicHull<ll> dynamicHull;
    dynamicHull.insert_line(-x, 0);
    ll dp = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        dp = -dynamicHull.eval(s[i]);
        dynamicHull.insert_line(-f[i], -dp);
    }
    cout << dp;
}