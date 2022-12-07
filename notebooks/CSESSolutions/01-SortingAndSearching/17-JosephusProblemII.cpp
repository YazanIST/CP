// Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, repeatedly k children are skipped and one child is removed from the circle. In which order will the children be removed?
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
int main() {
    int n, k;
    cin >> n >> k;
    ordered_set st;
    for (int i = 1; i <= n; i++) st.insert(i);
    int cur = 0;
    while (!st.empty()) {
        cur = (cur + k) % (int)st.size();
        cout << *st.find_by_order(cur) << ' ';
        st.erase(st.find_by_order(cur));
    }
}