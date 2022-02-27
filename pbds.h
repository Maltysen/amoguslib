#pragma once

#ifndef COPIER
    #include <bits/extc++.h>
#else
    TEMP_INCLUDE_EXT
#endif

using namespace __gnu_pbds;

template <class T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class K, class V>
using o_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
