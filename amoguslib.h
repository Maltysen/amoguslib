#pragma once

#ifndef COPIER
    #include "bits/stdc++.h"
#elif __CYGWIN__ || _WIN32 || _WIN64
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

template<class K, class V, int L=8, bool alloc=true> struct amogus_map{};

#define used(x) ((used_arr[x/8]>>(x%8))&1)
#define sused(x) ({used_arr[x/8] |= (1<<(x%8));})
// got this hash from KACTL
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/HashMap.h
const uint64_t __AMOGUSMAP_HASH_C = uint64_t(4e18 * acos(0)) | 71;

//const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
//int h = __builtin_bswap64(__AMOGUSMAP_HASH_C*(hash<K>{}(x) ^ RANDOM)) & ((1<<__res)-1); // if u're worried about hacking

#define find_val(x) int h = __builtin_bswap64(__AMOGUSMAP_HASH_C*hash<K>{}(x)) & ((1<<__res)-1); \
    while (used(h) && table[h]!=x) h = (h+1) & ((1<<__res)-1);
#define MAKEIF(O,T) template<class U=V> typename enable_if<O is_empty<U>::value, T>::type
template<class K, class V, int L>
struct amogus_map<K,V,L,false> {
    const int __res = L;
    K table[1<<L];
    V value[1<<L];
    char used_arr[1<<(L-3)];
    int __size=0;

    MAKEIF(!, V&)
    operator[](const K &x) {
        find_val(x)
        if (!used(h)) {
            table[h]=x, sused(h), __size++, value[h]=V{};
        }
        return value[h];
    }

    bool count(const K&x) const {
        find_val(x)
        return used(h);
    }

    MAKEIF(!, bool)
    insert(const pair<K, V> &p) {
        find_val(p.K)
        if (!used(h)) {
            table[h]=p.K, sused(h), value[h]=p.V, __size++;
            return true;
        }
        return false;
    }

    MAKEIF(,bool)
    insert(const K &k) {
        find_val(k)
        if (!used(h)) {
            table[h]=k, sused(h), __size++;
            return true;
        }
        return false;
    }
    void clear() {memset(used_arr, 0, 1<<(L-3));  __size=0;}
    int size() {return __size;}
};

template<class K, class V, int L>
struct amogus_map<K,V,L,true> {
    int __res = L;
    int __size=0;
    K* table = new K[1<<__res];
    V* value = new V[1<<__res];
    char *used_arr = new char[1<<(__res-3)]();

    bool CHKLOADF() {
        if (__size*3 > (1<<__res)) {
            __res++;
            K* ot=table; V* ov=value; char* ou = used_arr;
            table=new K[1<<__res]; value=new V[1<<__res]; used_arr = new char[1<<(__res-3)]();
            for (int i=0; i<(1<<(__res-1)); ++i) {
                if (((ou[i/8]>>(i%8))&1)) {
                    K k = ot[i];
                    find_val(k)
                    table[h]=k, sused(h), value[h]=ov[i];
                }
            }
            delete[]ot; delete[] ou; delete[] ov;
            return true;
        }
        return false;
    }

    MAKEIF(!, V&)
    operator[](const K &x) {
        find_val(x)
        if (!used(h)) {
            table[h]=x, sused(h), __size++, value[h]=V{};
            if (CHKLOADF()) return (*this)[x];
        }
        return value[h];
    }

    bool count(const K&x) const {
        find_val(x)
        return used(h);
    }

    MAKEIF(!, bool)
    insert(const pair<K, V> &p) {
        find_val(p.K)
        if (!used(h)) {
            table[h]=p.K, sused(h), value[h]=p.V, __size++;
            CHKLOADF();
            return true;
        }
        return false;
    }

    MAKEIF(,bool)
    insert(const K &k) {
        find_val(k)
        if (!used(h)) {
            table[h]=k, sused(h), __size++;
            CHKLOADF();
            return true;
        }
        return false;
    }

    void clear() {memset(used_arr, 0, 1<<(__res-3));  __size=0;}
    int size() {return __size;}

    ~amogus_map(){delete[] used_arr; delete[] table; delete[] value;};
};

#undef find_val
#undef used
#undef sused
#undef MAKEIF

template<class T, int L=8, bool alloc=true>
using amogus_set = amogus_map<T, tuple<>, L, alloc>;

#define IDT(T, idv...) static constexpr T id() {return idv;}

template<class T, int __NN, T(* f)(T, T)>
struct segtree {
    T t[2 * __NN];
    ll n=__NN;  // array size

    void modify(ll p, T value) {  // set value at position p
      for (p+=n, t[p] = value; p /= 2;) t[p] = f(t[2*p], t[2*p+1]);
    }

    T query(ll l, ll r) { // fold f on interval [l, r)
      T resl=T::id(), resr=T::id();
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

// TODO miller rabin

//////////////// TYPEDEFS ///////////////

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

/////////////////// MACROS AND I/O ///////////////////////

#define K first
#define V second

// This has all containers and pair
template<class T, class S>
ostream& operator<<(ostream& o, pair<T, S> p) {
	return o<<'('<<p.K<<", "<<p.V<<')';
}

template<template<class, class...> class T, class... A>
typename enable_if<!(is_same<T<A...>, string>() || is_same<T<A...>, complex< tuple_element_t<0, tuple<A...>> >>()), ostream&>::type
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

