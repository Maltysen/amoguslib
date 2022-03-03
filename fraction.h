#pragma once

bb gcd(bb x, bb y) {return y ? gcd(y, x%y) : x;}

struct fr {
    bb n, d;
    fr()=default;
    fr(bb a, bb b) {
        bb g = gcd(a,b);
        n=a/g, d=b/g;
        if (d<0) {
            d*=-1, n*=-1;
        }
    }
    fr (bb a) {n = a; d=1;}
};

fr operator+(fr a, fr b) {return fr(a.n*b.d + b.n*a.d, a.d*b.d);}
fr operator-(fr a, fr b) {return fr(a.n*b.d - b.n*a.d, a.d*b.d);}
fr operator*(fr a, fr b) {return fr(a.n*b.n, a.d*b.d);}
fr operator/(fr a, fr b) {return fr(a.n*b.d, a.d*b.n);}
ostream &operator<<(ostream &o, fr f) {return o<<(ll)f.n<<'/'<<(ll)f.d;}
