#pragma once

#include <linalgmod.h>

mat matmul_f2(const mat &a, const mat &b) {
    vector<bitset<BB>> A(a.size()), B(b[0].size()), C(a.size());
    mat bt = transpose(b);
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<a[0].size(); ++j) 
            A[i][j]=a[i][j], B[i][j]=bt[i][j];

    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<b[0].size(); ++j)
            C[i][j] = (A[i] ^ B[j]).count()&1;

    mat c(a.size(), vector<ll>(b[0].size()));
    for (int i=0; i<a.size(); ++i)
        for (int j=0; j<b[0].size(); ++j) c[i][j] = C[i][j];
    return c;
}

// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
int solve_system_f2(mat A, bitset<BB> &b) {
    int n=A.size();
    int m=A[0].size();
    vector<bitset<BB>> a(n);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) a[i][j]=A[i][j];
        a[i][m] = b[i];
    }

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
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }

    b.reset();
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            b[i] = a[where[i]][m];

    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j)
            sum ^= b[j]&a[i][j];
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

