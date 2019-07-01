#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <class Key, class T = null_type, class Compare = less<Key>>
using ordered_set_t = tree<Key, T, Compare, rb_tree_tag, tree_order_statistics_node_update>;

/**
 * ordered_map_t == ordered_t<Key, T>;
 * ordered_set_t == ordered_t<Key, null_type>;
 * 
 * .order_of_key(const Key x)     - return the number of elements less than 'x'
 * .find_by_order(const size_t n) - return the 'n-th' (0-indexed) smallest number stored in this tree
**/
