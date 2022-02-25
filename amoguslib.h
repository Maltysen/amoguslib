#pragma once

#ifndef COPIER
    #include "bits/stdc++.h"
#else
    TEMP_INCLUDE_BITS
#endif
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pl;
typedef vector<ll> vl;
#define all(x) begin(x), end(x)

/////////////// DATA STRUCTURES ///////////////////

template<class K, class V, int L=20>
struct amogus_map {
    int mod_mask = ((1<<L)-1);
    K table[1<<L];
    bitset<1<<L> used;
    V value[1<<L];
    int __size=0;

    // got this hash from KACTL
    // https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/HashMap.h
    const uint64_t C = uint64_t(4e18 * acos(0)) | 71;
    
    //const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
    #define __HASH(x) int h = __builtin_bswap64(C*hash<K>{}(x)) & mod_mask;
    //int h = __builtin_bswap64(C*(hash<K>{}(x) ^ RANDOM)) & mod_mask; // if u're worried about hacking

    V& operator[](const K &x) {
        __HASH(x)
        while (used[h] && table[h]!=x) {
            h = (h+1)&mod_mask;
        }
        if (!used[h]) {
            table[h]=x, used[h]=1, __size++;
        }
        return value[h];
    }

    bool count(const K&x) const {
        __HASH(x)
        while (used[h] && table[h]!=x) {
            h = (h+1)&mod_mask;
        }
        return used[h];
    }

    template<class U=V>
    typename enable_if<!is_empty<U>::value, bool>::type
    insert(const pair<K, V> &p) {
        __HASH(p.K)
        while (used[h] && table[h]!=p.K) {
            h = (h+1)&mod_mask;
        }
        if (!used[h]) {
            table[h]=p.K, used[h]=1, value[h]=p.V, __size++;
            return true;
        }
        return false;
    }

    template<class U=V>
    typename enable_if<is_empty<U>::value, bool>::type
    insert(const K &k) {
        __HASH(k)
        while (used[h] && table[h]!=k) {
            h = (h+1)&mod_mask;
        }
        if (!used[h]) {
            table[h]=k, used[h]=1, __size++;
            return true;
        }
        return false;
    }

    #undef __HASH

    void clear() {used.reset(); __size=0;}

    int size() {return __size;}
};

template<class T>
using amogus_set = amogus_map<T, tuple<>>;

template<class T, int __NN, T id, T(* f)(T, T)>
struct segtree {
    T t[2 * __NN];
    ll n=__NN;  // array size

    void modify(ll p, T value) {  // set value at position p
      for (p+=n, t[p] = value; p /= 2;) t[p] = f(t[2*p], t[2*p+1]);
    }

    T query(ll l, ll r) { // fold f on interval [l, r)
      T resl=id, resr=id;
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l&1) resl = f(resl, t[l++]);
        if (r&1) resr = f(t[--r], resr);
      }
      return f(resl, resr);
    }
};

/////////////// NUMBER THEORY ///////////

#include <prime.h>

ll inv(ll a, ll b){return 1<a ? b - inv(b%a,a)*b/a : 1;}

// TODO: non coprime moduli
ll CRT(const vector<ll> &a, const vector<ll> &n) {
  ll prod = 1;
  for (auto ni:n) prod*=ni;

  ll sm = 0;
  for (int i=0; i<n.size(); i++) {
    ll p = prod/n[i];
    sm += a[i]*inv(p, n[i])*p;
  }
  return sm % prod;
}

//////////////// TYPEDEFS ///////////////

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

template <class T>
using ordered_set<T> = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class K, V>
using ordered_map<K, V> = tree<T, V, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/////////////////// MACROS AND I/O ///////////////////////

#define K first
#define V second

// This has all containers and pair
template<class T, class S>
ostream& operator<<(ostream& o, pair<T, S> p) {
	return o<<'('<<p.K<<", "<<p.V<<')';
}

template<template<class, class...> class T, class... A>
typename enable_if<!(is_same<T<A...>, string>() || is_same<T<A...>, complex<ld>>()), ostream&>::type
operator<< (ostream& o, T<A...> v) {
	o<<'[';
	for (auto a:v) o<<a <<", ";
	return o<<']';
}

// This is tuples, _p is helper
template<ll i, class... T>
typename enable_if<i==sizeof...(T)>::type _p(ostream& o, tuple<T...> t) {}

template<ll i, class... T>
typename enable_if<i<sizeof...(T)>::type _p(ostream& o, tuple<T...> t) {
    _p<i+1>(o << get<i>(t)<< ", ", t);
}

template<class... T>
ostream& operator<<(ostream& o, tuple<T...> t) {
    _p<0>(o<<'(', t);
    return o<<')';
}

void _print() {cerr << "]"<<endl;} template <class T, class... V>
void _print(T t, V... v) {cerr<<t; if (sizeof...(v)) cerr << ", "; _print(v...);}

#ifdef ONLINE_JUDGE
    #define __DEBUG_PRINT(x...) do {} while(0);
#else
    #define __DEBUG_PRINT(x...) do {cerr << "[" << #x << "] = ["; _print(x); } while(0);
#endif

#define D(x...) __DEBUG_PRINT(x)

#define TIE(a, b, _p) auto __p = _p; auto a = __p.first; auto b = __p.second;

#define TC ll ntests;cin>>ntests;ll tc=0;goto _restart;_restart:;while(++tc<=ntests)
#define EXT(x) {cout<<x<<'\n'; goto _restart;}
#define EX(x) {cout<<x<<'\n'; exit(0);}
#define SP(x) setprecision(x)

