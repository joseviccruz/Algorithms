#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T1, typename T2 = null_type, typename T3 = less<T1>>
using indexed_tree = tree<T1, T2, T3, rb_tree_tag, tree_order_statistics_node_update>;

/**
 * indexed_map == indexed_tree<T1, T2>;
 * indexed_set == indexed_tree<T1, null_type>;
 * 
 * .order_of_key(const T1 x)      - return the number of elements less than 'x'
 * .find_by_order(const size_t n) - return the 'n-th' (0-indexed) smallest number stored in this tree
**/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
