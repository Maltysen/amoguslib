#pragma once

template<class T, int __NN, T(* f)(T, T)>
struct inverse_segtree {
    T t[2 * __NN];
    int n=__NN;  // array size
    T id;

    inverse_segtree(){} inverse_segtree(T idv) {
        id=idv; fill(t, t+2*n, id);
    }

    void modify(int l, int r, T v) {
        for (l+=n, r+=n; l<r; l/=2, r/=2) {
            if (l&1) t[l] = f(t[l], v), l++;
            if (r&1) --r, t[r] = f(t[r], v);
        }
    }

    T query(int p) {
        T res = id;
        for (p+=n; p>0; p/=2) res = f(res, t[p]);
        return res;
    }

    void push() {
        for (int i=1; i<n; ++i) {
            t[i*2] = f(t[i*2], t[i]);
            t[i*2+1] = f(t[i*2+1], t[i]);
            t[i] = 0;
        }
    }
};

template<class T, class U, int __NN, T(*f)(T, T), U(*g)(U, U), T(*h)(U, T), int L=26>
struct lazy_segtree {
	T t[2 * NN];
	U d[NN];
    T idT; U idU;
	ll n = NN;

    lazy_segtree(T id1, U id2) {
        idT=id1; idU=id2;
        fill(d, d+n, idU);
    }

    void calc(int p) {
        t[p] = h(d[p], f(t[p*2], t[p*2+1]));
    }

    void apply(int p, U v) {
        t[p] = h(v, t[p]);
        if (p<n) d[p] = g(v, d[p]);
    }

    void build(int l, int r) {
        for (l+=n, r+=n-1; l>1; ) {
            l/=2, r/=2;
            for (int i=r; i>=l; --i) calc(i);
        }
    }

    void push(int l, int r) {
        int s=L;
        for (l+=n, r+=n-1; s>0; --s) {
            for (int i=l>>s; i<=r>>s; ++i) if (d[i]!=idU) {
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
                d[i]=idU;
            }
        }
    }

    void modify(int p, T v) {
        push(p, p+1);
        t[p+n] = v;
        build(p, p+1);
    }

    void modify(int l, int r, U v) {
        if (v==idU) return;
        push(l, l+1);
        push(r-1, r);
        int l0=l, r0=r;
        for (l+=n, r+=n; l<r; l/=2, r/=2) {
            if (l&1) apply(l++, v);
            if (r&1) apply(--r, v);
        }
        build(l0, l0+1);
        build(r0-1, r0);
    }

    T query(int l, int r) {
        push(l, l+1);
        push(r-1, r);
        T resl=idT, resr=idT;
        for (l += n, r += n; l < r; l/=2, r/=2) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        return f(resl, resr);
    }
};
