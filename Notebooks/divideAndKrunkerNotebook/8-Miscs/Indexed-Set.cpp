#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

template <typename K>
using indexed_set = tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    indexed_set<pair<int,int>> st;
}