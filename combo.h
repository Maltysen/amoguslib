#pragma once

#include <modular.h>

ll choose(ll n, ll k) {
    if (k>n) return 0;
    return f[n] *fi[n-k]%M * fi[k]%M;
}

ll choose_with_repl(ll n, ll k) {
    return choose(n+k-1, k);
}

ll catalan(ll n) {
    return choose(2*n, n)*inv(n+1)%M;
}

#define DO_FACS() ({f[0]=fi[0] = 1; for (int i=1; i<NN; ++i) {f[i]=f[i-1]*i%M; fi[i]=fi[i-1]*inv(i)%M;} })
