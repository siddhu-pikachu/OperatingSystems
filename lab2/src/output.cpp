#include "output.h"
#include "logger.h"
#include "matrix.h"
#include "exceptions.h"

#include <bits/stdc++.h>


void output::matrixEvaluation(std::vector<std::vector<std::vector<long long>>> &matrices, std::vector<long long> &scalars, char &optFlag, std::vector<char> ord)
{
    // std::cout<<"hello======================output.cpp"<<std::endl;
    if (LOGGER::stlogfile.is_open())
    {
        LOGGER::stlogfile << "In output.cpp (matrixEvaluation function)...\n";
    }
    else
    {
        throw exceptions::file_notfound();
    }
    // matrices contains all the matrices stored for operations
    // scalars contains all the scalars stored for operations with matrices
    // ord contains the order in which scalars and matrices are present in the file so that we can do operations 

    bool isMatrixRes=true;
    long long m=0,s=0,ord_ind=0,scalar_res=0;
    std::vector<std::vector<long long>> matrx_res;

    // atmost two matrices will be given
    char option = optFlag;
    if(option == 'a' or option == 'A' or option == 's' or option == 'S' or option == 'm' or option == 'M' or option == 'd')
    {
        if (ord_ind + 1 >= ord.size()) {std::cout<<"1"<<std::endl;throw exceptions::outof_bounds();}
        if(ord[ord_ind]=='0' and ord[ord_ind+1]=='0')
        {
            throw exceptions::unsupported_operation();
        }
        else if(ord[ord_ind]=='1' and ord[ord_ind+1]=='1') // both are matrices
        {
            if(m+1>=matrices.size())
            {
                throw exceptions::invalid_input();
            }
            isMatrixRes = true;
            switch(option)
            {
                case 'A' : matrx_res = matrix::matrix_add(matrices[m], matrices[m+1]);break;
                case 'S' : matrx_res = matrix::matrix_sub(matrices[m], matrices[m+1]);break;
                case 'M' : matrx_res = matrix::matrix_mul(matrices[m], matrices[m+1]);break;
            }
            m=m+2;
        }
        else // matrix and scalar
        {
            if(m+1>matrices.size() or s+1>scalars.size())
            {
                std::cout<<"2"<<std::endl;
                throw exceptions::outof_bounds();
            }
            isMatrixRes=true;
            switch(option)
            {
                case 'a' : matrx_res = matrix::scalar_add(matrices[m],scalars[s]);break;
                case 's' : matrx_res = matrix::scalar_sub(matrices[m],scalars[s]);break;
                case 'm' : matrx_res = matrix::scalar_mul(matrices[m],scalars[s]);break;
                case 'd' : matrx_res = matrix::scalar_div(matrices[m],scalars[s]);break;
            }
            m++,s++;
        }
        ord_ind+=2;
    }
    else if(option == 'T')
    {
        if(ord_ind>=ord.size())
        {
            std::cout<<"3"<<std::endl;
            throw exceptions::outof_bounds();
        }
        if(ord[ord_ind]=='0')
        {
            throw exceptions::unsupported_operation();
        }
        if(m>=matrices.size())
        {
            std::cout<<"4"<<std::endl;
            throw exceptions::outof_bounds();
        }
        isMatrixRes=true;
        int temp=0;
        matrx_res = matrix::matrix_transpose(matrices[m]);
        m++,ord_ind++;
    }
    else if(option=='X')
    {
        if(ord_ind>=ord.size())
        {
            throw exceptions::outof_bounds();
        }
        if(ord[ord_ind]=='0')
        {
            throw exceptions::unsupported_operation();
        }
        if(m>=matrices.size())
        {
            throw exceptions::outof_bounds();
        }
        int temp=0;
        isMatrixRes=false;
        scalar_res=matrix::matrix_determinant(matrices[m]);
        m++,ord_ind++;
    }
    else
    {
        throw exceptions::invalid_arguments();
    }
    // FILE* fp;
    // fp = fopen("final_output.txt","w");
    // std::cout<<"ismatrix "<<isMatrixRes<<std::endl;
        // std::cout<<"hello======================output.cpp"<<std::endl;
    if(isMatrixRes)
    {
        long long rr = matrx_res.size();
        long long cc = matrx_res[0].size();
        // fprintf(fp,"%lld %lld\n",rr,cc);
        // std::cout<<rr<<" "<<cc<<std::endl;
        for(long long i=0;i<rr;i++)
        {
            for(long long j=0;j<cc;j++)
            {
                // fprintf(fp,"%lld,", matrx_res[i][j]);
                std::cout<<matrx_res[i][j]<<",";
            }
            // fprintf(fp,"\n");
            std::cout<<std::endl;
        }
        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile << "Resulatant Matrix: \n";
            for(long long i=0;i<rr;i++)
            {
                for(long long j=0;j<cc;j++)
                {
                    LOGGER::stlogfile << matrx_res[i][j] << ",";
                }
                LOGGER::stlogfile << "\n";
            }
            LOGGER::stlogfile << "\n";
        }
        else
        {
            throw exceptions::file_notfound();
        }
    }
    else
    {
        // fprintf(fp,"%lld" , scalar_res);
        std::cout<<scalar_res<<std::endl;
        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile << "Resultant Scalar: " << scalar_res <<"\n";
        }
        else
        {
            throw exceptions::file_notfound();
        }
    }
    // fclose(fp);
    return;
}