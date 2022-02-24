#pragma ONCE

ll phi(ll n) {
  ll ans = n;
  while (n>1) {
    ll p = prime[n];
    while (n%p==0) n/=p;
    ans = ans/p*(p-1);
  }
  return ans;
}
