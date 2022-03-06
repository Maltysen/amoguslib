#pragma once

ll powmod(ll x, ll y){
  ll r=1;
  while (y) {
    if (y%2) r = r*x%M;
    x = x*x%M;
    y/=2;
  }
  return r;
}

ll powmod(ll x, ll y, ll m) {
  ll r=1;
  while (y) {
    if (y%2) r = r*x%m;
    x = x*x%m;
    y/=2;
  }
  return r;
}

ll inv(ll a) {return inv(a, M);}
