// A company has n employees with certain salaries. Your task is to keep track of the salaries and process queries.
struct Query {
    char type;
    int a, b, aMapped, bMapped;
};
vector<int> compress(const vector<int> &v) {
    set<int> st(v.begin(), v.end());
    return vector<int>(st.begin(), st.end());
}
int main() {
    int n, q;
    cin >> n >> q;
    set<int> st;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        st.insert(x);
    }
    vector<Query> queries(q);
    for (auto &x : queries) {
        cin >> x.type >> x.a >> x.b;
        if (x.type == '?')
            st.insert(x.a);
        st.insert(x.b);
    }
    vector<int> compressed(st.begin(), st.end());
    vector<int> mapped;
    for (int i = 0; i < (int)a.size(); ++i) {
        int value = a[i];
        int newValue = lower_bound(compressed.begin(), compressed.end(), value) - compressed.begin();
        mapped.push_back(newValue);
    }
    for (auto &x : queries) {
        if (x.type == '?') {
            int value1 = x.a;
            int newValue1 = lower_bound(compressed.begin(), compressed.end(), value1) - compressed.begin();
            x.aMapped = newValue1;
        }
        int value2 = x.b;
        int newValue2 = lower_bound(compressed.begin(), compressed.end(), value2) - compressed.begin();
        x.bMapped = newValue2;
    }
    Fenwick<int> ft(st.size());
    for (auto x : mapped) ft.add(x, 1);
    for (auto query : queries) {
        if (query.type == '!') {
            ft.add(mapped[query.a - 1], -1);
            ft.add(query.bMapped, 1);
            a[query.a - 1] = query.b;
            mapped[query.a - 1] = query.bMapped;
        } else {
            cout << ft.sum(query.aMapped, query.bMapped) << '\n';
        }
    }
}