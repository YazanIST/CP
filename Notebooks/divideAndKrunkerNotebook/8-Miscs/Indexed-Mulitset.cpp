#include <ext/pb_ds/assoc_container.hpp>
#include "bits/stdc++.h"
 
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
template <typename T> using indexed_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

/*
If we want to get map but not the set, as the second argument type must be used mapped type.
Apparently, the tree supports the same operations as the set (at least I haven't 
any problems with them before),
but also there are two new features — it is find_by_order() and order_of_key().
The first returns an iterator to the k-th largest element (counting from zero),
 the second — the number of items in a set that are strictly smaller than our item.
*/

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    indexed_set<int> st;
    for (int i = 0; i < k; i++) {
        st.insert(a[i]);
    }

    int l = 0, r = k, target = (k - 1) / 2;
    while (r < n) {
        auto it = st.find_by_order(target);
        cout << *it << ' ';

        st.erase(st.upper_bound(a[l]));
        st.insert(a[r]);
        l++, r++;
    }
    auto it = st.find_by_order(target);
    cout << *it << ' ';
}