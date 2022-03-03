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
        t[p] = f(t[p*2], t[p*2+1]);
        if (d[p]!=idU) t[p] = h(d[p], t[p]);
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

    void push(int p) {
        p+=n;
        for (int s=L; s>0; --s) {
            int i=p>>s;
            if (d[i]!=idU) {
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
                d[i]=idU;
            }
        }
    }

    void modify(int p, T v) {
        push(p);
        t[p+n] = v;
        build(p, p+1);
    }

    void modify(int l, int r, U v) {
        if (v==idU) return;
        push(l), push(r-1);
        bool cl=false, cr=false;
        for (l+=n, r+=n; l<r; l/=2, r/=2) {
            if (cl) calc(l-1);
            if (cr) calc(r);
            if (l&1) apply(l++, v), cl=true;
            if (r&1) apply(--r, v), cr=true;
        }
        for (--l; r>0; l/=2, r/=2) {
            if (cl) calc(l);
            if (cr && (!cl || l != r)) calc(r);
        }
    }

    T query(int l, int r) {
        push(l), push(r-1);
        T resl=idT, resr=idT;
        for (l += n, r += n; l < r; l/=2, r/=2) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        return f(resl, resr);
    }
};
