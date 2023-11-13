#include <bits/stdc++.h>

#include "matrix.h"
#include "exceptions.h"


// using namespace std;

// For scalar and matrix operations

std::vector<std::vector<long long>> matrix::scalar_add(std::vector<std::vector<long long>> &mtx, long long num)
{
    long long numr=mtx.size();
    long long numc=mtx[0].size();
    std::vector<std::vector<long long>> res_mtx(numr,std::vector<long long>(numc,0));
    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_mtx[r][c]=mtx[r][c]+num;
        }
    }
    return res_mtx;
}

std::vector<std::vector<long long>> matrix::scalar_sub(std::vector<std::vector<long long>> &mtx, long long num)
{
    long long numr=mtx.size();
    long long numc=mtx[0].size();
    std::vector<std::vector<long long>> res_mtx(numr,std::vector<long long>(numc,0));
    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_mtx[r][c]=mtx[r][c]-num;
        }
    }
    return res_mtx;
}

std::vector<std::vector<long long>> matrix::scalar_mul(std::vector<std::vector<long long>> &mtx, long long num)
{
    long long numr=mtx.size();
    long long numc=mtx[0].size();
    std::vector<std::vector<long long>> res_mtx(numr,std::vector<long long>(numc,0));
    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_mtx[r][c]=mtx[r][c]*num;
        }
    }
    return res_mtx;
}

std::vector<std::vector<long long>> matrix::scalar_div(std::vector<std::vector<long long>> &mtx, long long num)
{
    long long numr=mtx.size();
    long long numc=mtx[0].size();
    std::vector<std::vector<long long>> res_mtx(numr,std::vector<long long>(numc,0));
    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            if(num==0)
            {
                throw exceptions::divideby_zero();
            }
            res_mtx[r][c]=mtx[r][c]/num;
        }
    }
    return res_mtx;
}

// For matrix and matrix operations

std::vector<std::vector<long long>> matrix::matrix_add(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2)
{
    long long numr=mtx1.size();
    long long numc=mtx1[0].size();
    long long numr1=mtx2.size();
    long long numc1=mtx2[0].size();

    if(numr!=numr1 or numc!=numc1)
    {
        throw exceptions::invalid_dimensions();
    }
    
    std::vector<std::vector<long long>> res_matrix (numr,std::vector<long long>(numc,0));

    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_matrix[r][c]=mtx1[r][c]+mtx2[r][c];
        }
    }
    return res_matrix;   
}

std::vector<std::vector<long long>> matrix::matrix_sub(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2)
{
    long long numr=mtx1.size();
    long long numc=mtx1[0].size();
    long long numr1=mtx2.size();
    long long numc1=mtx2[0].size();

    if(numr!=numr1 or numc!=numc1) {throw exceptions::invalid_dimensions();}
    
    std::vector<std::vector<long long>> res_matrix (numr,std::vector<long long>(numc,0));

    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_matrix[r][c]=mtx1[r][c]-mtx2[r][c];
        }
    }
    return res_matrix;   
}

std::vector<std::vector<long long>> matrix::matrix_mul(std::vector<std::vector<long long>> &mtx1, std::vector<std::vector<long long>> &mtx2)
{
    long long numr=mtx1.size();
    long long numc=mtx1[0].size();
    long long numr1=mtx2.size();
    long long numc1=mtx2[0].size();

    if(numc!=numr1) {throw exceptions::invalid_dimensions();}
    
    std::vector<std::vector<long long>> res_matrix (numr,std::vector<long long>(numc1,0));

    for(long long r=0;r<numr;r++)
    {
        for(long long c1=0;c1<numc1;c1++)
        {
            for(long long c=0;c<numc;c++)
            {
                res_matrix[r][c1] += mtx1[r][c] * mtx2[c][c1];
            }
        }
    }
    return res_matrix;
}

std::vector<std::vector<long long>> matrix::matrix_transpose (std::vector<std::vector<long long>> &mtx1)
{
    // transpose matrix has numc rows and numr columns
    long long numr=mtx1[0].size();
    long long numc=mtx1.size();
    std::vector<std::vector<long long>> res_matrix (numr,std::vector<long long>(numc,0));
    for(long long r=0;r<numr;r++)
    {
        for(long long c=0;c<numc;c++)
        {
            res_matrix[r][c] = mtx1[c][r];
        }
    }
    return res_matrix;
}

std::vector<std::vector<long long>> matrix::getCofactor(long long r, long long c, std::vector<std::vector<long long>> m)
{

    long long mr = m.size(), mc = m[0].size();
    std::vector<std::vector<long long>> res(mr - 1, std::vector<long long>(mc - 1, 0));

    if(mr>=2 and mc>=2)
    {
        if(r>=0 and c>=0 and r<mr and c<mc)
        {
            long long resr = 0, resc = 0;
            for (long long i = 0; i < mr; ++i)
            {
                if(i!=r)
                {
                    for (long long j = 0; j < mc; ++j)
                    {
                        if (j == c) continue;
                        res[resr][resc++] = m[i][j];
                    }
                    ++resr;
                    resc = 0;
                }
                
            }
        }
        else {throw exceptions::outof_bounds();}
    }
    else {throw exceptions::invalid_arguments();}
    

    return res;
}


long long matrix::det_helper (const std::vector<std::vector<long long>> &m,long long numc)
{

    if (numc == 1) return m[0][0];

    long long det = 0,sign = 1;
    std::vector<std::vector<long long>> temp(numc,std::vector<long long>(numc,0));
    for (long long c = 0; c < numc; c++)
    {
        std::vector<std::vector<long long>> cofactor = getCofactor(0, c, m);
        det += (sign * m[0][c] * det_helper(cofactor, numc - 1));
        sign *= -1;
    }

    return det;
}


long long matrix::matrix_determinant(std::vector<std::vector<long long>> &mtx1)
{
    long long det = 0;

    long long numr=mtx1.size();
    long long numc=mtx1[0].size();

    if(numr != numc) {throw exceptions::nonsquare_matrix();}

    if(numr==1) return mtx1[0][0];

    det = det_helper(mtx1,numr);

    return det;
}
