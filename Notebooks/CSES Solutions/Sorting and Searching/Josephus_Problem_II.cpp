// 1 ≤ n ≤ 2e5
// 0 ≤ k ≤ 1e9
int main() {
    int n, k;
    cin >> n >> k;
    ordered_set st;
    for (int i = 1; i <= n; i++)
        st.insert(i);
    int cur = 0;
    while (!st.empty()) {
        cur = (cur + k) % (int)st.size();
        cout << *st.find_by_order(cur) << ' ';
        st.erase(st.find_by_order(cur));
    }
}