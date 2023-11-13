#ifndef MATRIX_H  // include guard
#define MATRIX_H

#include <bits/stdc++.h>

// using namespace std;

namespace matrix
{
    std::vector<std::vector<long long>> scalar_add(std::vector<std::vector<long long>> &mtx, long long num);
    std::vector<std::vector<long long>> scalar_sub(std::vector<std::vector<long long>> &mtx, long long num);
    std::vector<std::vector<long long>> scalar_mul(std::vector<std::vector<long long>> &mtx, long long num);
    std::vector<std::vector<long long>> scalar_div(std::vector<std::vector<long long>> &mtx, long long num);
    std::vector<std::vector<long long>> matrix_add(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2);
    std::vector<std::vector<long long>> matrix_sub(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2);
    std::vector<std::vector<long long>> matrix_mul(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2);
    std::vector<std::vector<long long>> matrix_transpose (std::vector<std::vector<long long>> &mtx1);
    std::vector<std::vector<long long>> getCofactor(long long r, long long c, std::vector<std::vector<long long>> m);
    long long det_helper (const std::vector<std::vector<long long>> &m,long long numc);
    long long matrix_determinant(std::vector<std::vector<long long>> &mtx1);
}

#endif