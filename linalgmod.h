#pragma once

#include <modular.h>

typedef vector<vector<ll>> mat;

mat operator*(const mat &a, const mat &b) {
    mat c(a.size(), vector<ll>(b[0].size()));

    for (int i=0; i<a.size(); ++i)
        for (int k=0; k<b.size(); ++k)
            for (int j=0; j<b[0].size(); ++j)
                ( c[i][j] += a[i][k]*b[k][j] )%=M;
    return c;
}

mat operator+(mat a, const mat&b) {
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            ( a[i][j] += b[i][j] )%=M;
    return a;
}

mat operator*(ll f, mat a) {
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            ( a[i][j] *= f )%=M;
    return a;
}

mat operator*(const mat &a, ll f) {return f*a;}
mat operator/(const mat &a, ll f) {return a*inv(f);}
mat operator-(const mat &a){return a*(M-1);}
mat operator-(const mat &a, const mat &b) {return a + -b;}

mat transpose(const mat &a) {
    mat b(a[0].size(), vector<ll>(a.size()));
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            b[j][i] = a[i][j];
    return b;
}

mat mat_id(int n) {
    mat a(n, vector<ll>(n));
    for (ll i=0; i<n; ++i) a[i][i]=1;
    return a;
}

mat exp_mat(const mat &x, ll y) {
    if (y==0) return mat_id(x.size());
    mat t = exp_mat(x, y/2);
    if (y%2) return t*t*x;
    return t*t;
}

// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
vector<int> where;
int solve_system(mat a, vector<ll> &b) {
    int n=a.size();
    int m=a[0].size();
    for (int i=0; i<n; ++i) a[i].push_back(b[i]);

    where.assign(m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap(a[i], a[row]);
                break;
            }
        if (!a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                ll c = a[i][col] * inv(a[row][col]) %M;
                for (int j=col; j<=m; ++j)
                    a[i][j] = ( a[i][j] - a[row][j]*c%M + M)%M;
            }
        ++row;
    }

    b.assign(m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            b[i] = a[where[i]][m] * inv(a[where[i]][i]) %M;
    for (int i=0; i<n; ++i) {
        ll sum = 0;
        for (int j=0; j<m; ++j)
           ( sum += b[j] * a[i][j] )%=M;
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

