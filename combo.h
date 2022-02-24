#pragma once

#include <modular.h>

ll choose(ll n, ll k) {
    if (k>n) return 0;
    return f[n] *f[n-k]%M * f[k]%M;
}

ll choose_with_repl(ll n, ll k) {
    return choose(n+k-1, k);
}

#define DO_FACS() ({f[0]=fi[0] = 1; for (int i=1; i<NN; ++i) {f[i]=f[i-1]*i%M; fi[i]=fi[i-1]*inv(i)%M;} })
