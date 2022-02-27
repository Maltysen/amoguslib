#pragma once

#include <bits/extc++.h>
using namespace __gnu_pbds;


template <class T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class K, V>
using o_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
