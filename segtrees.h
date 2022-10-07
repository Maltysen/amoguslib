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
	T t[2 * __NN];
	U d[__NN];
    T idT; U idU;
	ll n = __NN;

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

template<class K, class T, T(*f)(T, T)>
struct d2dseg {
    T id;

    struct seg {
        T* t, id;
        int n;

        void init(int nn, T idT) {
            id = idT;
            n = nn;
            t = new T[2*n];
            fill(t, t+2*n, id);
        }

        void modify(int p, T value) {  // set value at position p
            for (p+=n, t[p] = value; p /= 2;) t[p] = f(t[2*p], t[2*p+1]);
        }

        T query(int l, int r) { // fold f on interval [l, r)
            T resl=id, resr=id;
            for (l += n, r += n; l < r; l /= 2, r /= 2) {
                if (l&1) resl = f(resl, t[l++]);
                if (r&1) resr = f(t[--r], resr);
            }
            return f(resl, resr);
        }
    };

    using I=pair<K, int>;
    int n;
    K* keys;
    seg *s;
    I **k;

    int m;
    #define CH if(p>=n || (m=s[2*p].n)==s[2*p+1].n)
    void init(T idT) {
        id = idT;
        k = new I*[2*n];
        s = new seg[2*n];
        for (int p=2*n; --p;) CH {
            s[p].init(2*m + !m, id);
            k[p] = new I[s[p].n];
            I** y = k+2*p;
            m ? *merge(*y, *y+m, y[1], y[1]+m, k[p])
                : *k[p] = {keys[p-n], p-n};
        }
    }

    #define lb(a...) lower_bound(k[p], k[p]+s[p].n, I{a}) - k[p]
    void modify(int p, T v) {
        I a{keys[p], p};
        for (p+=n; p; p/=2) CH s[p].modify(lb(a), v);
    }

    #define qq(i) p=i, res=f(res, s[p].query(lb(a, -1), lb(b, -1)));
    T query(int l, int r, K a, K b) {
        int p;
        T res=id;
        for (l+=n, r+=n; l<r; l/=2, r/=2) {
            if (l&1) qq(l++)
            if (r&1) qq(--r)
        }
        return res;
    }

    #undef CH
    #undef lb
    #undef qq
};
