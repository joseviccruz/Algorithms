#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename Key, typename T = null_type, typename Compare = less<Key>>
using indexed_tree = tree<Key, T, Compare, rb_tree_tag, tree_order_statistics_node_update>;

/**
 * indexed_map == indexed_tree<Key, T>;
 * indexed_set == indexed_tree<Key, null_type>;
 * 
 * .order_of_key(const Key x)      - return the number of elements less than 'x'
 * .find_by_order(const size_t n) - return the 'n-th' (0-indexed) smallest number stored in this tree
**/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
