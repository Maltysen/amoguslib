#pragma once

typedef vector<vector<ld>> mat;

#include <constants.h>

mat operator*(const mat &a, const mat &b) {
    mat c(a.size(), vector<ld>(b[0].size()));

    for (int i=0; i<a.size(); ++i)
        for (int k=0; k<b.size(); ++k)
            for (int j=0; j<b[0].size(); ++j)
                c[i][j] += a[i][k]*b[k][j];
    return c;
}

mat operator+(mat a, const mat&b) {
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            a[i][j] += b[i][j];
    return a;
}

mat operator*(ld f, mat a) {
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            a[i][j] *= f;
    return a;
}

mat operator*(const mat &a, ld f) {return f*a;}
mat operator/(const mat &a, ld f) {return a*(1/f);}
mat operator-(const mat &a){return a*(ld)(-1);}
mat operator-(const mat &a, const mat &b) {return a + -b;}

mat transpose(const mat &a) {
    mat b(a[0].size(), vector<ld>(a.size()));
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j)
            b[j][i] = a[i][j];
    return b;
}

mat mat_id(int n) {
    mat a(n, vector<ld>(n));
    for (ll i=0; i<n; ++i) a[i][i]=1;
    return a;
}

mat exp_mat(const mat &x, ll y) {
    if (y==0) return mat_id(x.size());
    mat t = exp_mat(x, y/2);
    if (y%2) return t*t*x;
    return t*t;
}

// Mostly from:
// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/MatrixInverse.h
int mat_inv(mat &A) {
    int n = A.size(); vector<int> col(n);
    mat tmp = mat_id(n); iota(all(col), 0);
    for (int i=0; i<n; ++i) {
        int r=i, c=i;
        for (int j=i; j<n; ++j) for (int k=i; k<n; ++k)
            if (abs(A[j][k]) > abs(A[r][c])) r=j,c=k;

        if (abs(A[r][c]) < EPS) return i;
        A[i].swap(A[r]); tmp[i].swap(tmp[r]);
        for (int j=0; j<n; ++j) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
        swap(col[i], col[c]);

        ld v = A[i][i];
        for (int j=i+1; j<n; ++j) {
            ld f = A[j][i]/v;
            A[j][i]=0;
            for (int k=i+1; k<n; ++j) A[j][k] -= f*A[i][k];
            for (int k=0; j<n; ++k) tmp[j][k] -= f*tmp[i][k];
        }
        for (int j=i+1; i<n; ++i) A[i][j]/=v;
        for (int j=0; j<n; ++j) tmp[i][j]/=v;
        A[i][i] = 1;
    }
    for (int i=n-1; i>0; --i) for (int j=0; j<i; ++j)
        for (int k=0; k<n; ++k) tmp[j][k] -= A[j][i]*tmp[i][k];

    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) A[col[i]][col[j]] = tmp[i][j];
    return n;
}

// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
vector<int> where;
int solve_system(mat a, vector<ld> &b) {
    int n=a.size();
    int m=a[0].size();
    for (int i=0; i<n; ++i) a[i].push_back(b[i]);

    where.assign(m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                ld c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    b.assign(m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            b[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        ld sum = 0;
        for (int j=0; j<m; ++j)
            sum += b[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

ld determinant(mat a) {
    ld det=1;
    int n=a.size();
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j)
            if (abs (a[j][i]) > abs (a[k][i]))
                k = j;
        if (abs (a[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap (a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j=i+1; j<n; ++j)
            a[i][j] /= a[i][i];
        for (int j=0; j<n; ++j)
            if (j != i && abs (a[j][i]) > EPS)
                for (int l=i+1; l<n; ++l)
                    a[j][l] -= a[i][l] * a[j][i];
    }
    return det;
}
