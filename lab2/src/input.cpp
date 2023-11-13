#include "input.h"
#include <unistd.h>
#include <stdio.h> 
#include <bits/stdc++.h>
#include <fstream>
#include <cctype>

#include "logger.h"
#include "matrix.h"
#include "exceptions.h"

bool input::checkValid(std::string &line)
{
    for(auto &c : line)
    {
        if(isdigit(c) || c==' ' || c==',' || c=='\n') continue;
        else return false;
    }
    return true;
}

bool input::checkMatrixValues(std::string line)
{
    auto res = line.find(',');
    if(res == std::string::npos) return false;
    return true;
}

bool input::checkMatrixDimensions(std::string line)
{
    auto res = line.find(' ');
    if(res == std::string::npos) return false;
    return true;
}

FILE* input::parser(int argc, char** argv, std::vector<char> &args,char &optFlag)
{
        // std::cout<<"hello======================input.cpp"<<std::endl;

    if (LOGGER::stlogfile.is_open())
    {
        LOGGER::stlogfile << "In input.cpp (parser function)...\n";
    }
    else
    {
        throw exceptions::file_notfound();
    }

    long long option = getopt(argc,argv,":aAsSmMdTX");
    while(option  != -1)
    {
        switch(option)
        {
            case 'a':
            case 's':
            case 'm':
            case 'd':
            case 'A':
            case 'S':
            case 'M':
            case 'T':
            case 'X':
                    args.push_back(option);break;
            case '?':
            default: 
                    throw exceptions::invalid_arguments();break;
        }
        option = getopt(argc,argv, ":aAsSmMdTX");
    }
    optFlag=args[0];

    char* filename;
    for(;optind<argc;optind++) // for extra arguments other than options (input file)
    {
        filename = argv[optind];
        break;
    }
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

void input::fileline_handler(std::vector<std::vector<std::vector<long long>>> &matrices, std::vector<long long> &scalars, std::vector<char> &order, FILE* fp)
{

    if (LOGGER::stlogfile.is_open())
    {
        LOGGER::stlogfile << "In input.cpp (fileline_hander function)...\n";
    }
    else
    {
        throw exceptions::file_notfound();
    }

    char ln[500];
    

    while (std::fgets(ln,sizeof(ln),fp)) // getline can be used in two ways
    {

        std::string line(ln);

        
        // remove front and back whitespaces
        long long ind = 0;
        long long len = line.length();
        
        for(ind=0;ind<len;ind++)
        {
            if(!isspace(line[ind])) break;
            if(isspace(line[ind])) {line.erase(ind,1);}
        }
        len = line.length();
        ind=len-1;
        if(len!=0)
        {
            for(ind=len-1;ind>=0;ind--)
            {
                if(line[ind]!=' ') break;
                if(line[ind]==' ') line.erase(ind,1);
            }
        }
        len=line.length();
        bool flag = false;
        if(len!=0 and line[0]!='#') flag=true; // check if the line is just a comment or just whitespaces

        if (flag==true) // scalar, matrix, dimensions
        {

            if (checkValid(line)==false || checkMatrixValues(line)==true)
            {
                throw exceptions::invalid_input();
            }
            else if (!checkMatrixDimensions(line)) // for scalars
            {
                scalars.push_back(std::stoll(line,nullptr,10));
                order.push_back('0');
            }
            else
            {
                std::stringstream s(line);  // stringstream allows us to read from the line
                std::string num = "";
                long long count = 0, numr = 0, numc = 0;
                while (std::getline(s, num, ' '))
                {
                    count++;
                    if (count == 1)
                    {
                        numr = std::stoll(num,nullptr,10);
                    }
                    else if (count == 2)
                    {
                        numc = std::stoll(num,nullptr,10);

                    }
                    else
                    {
                        throw exceptions::invalid_input();
                    }
                }
                std::vector<std::vector<long long>> mtx(numr,std::vector<long long>(numc,0));
                long long r=0,c=0;
                for(long long i=0;i<numr;i++)
                {
                    std::fgets(ln,sizeof(ln),fp);
                    std::string matrix_line(ln);
                    std::stringstream matrix_s(matrix_line);
                    std::string matrix_num="";
                    while(std::getline(matrix_s, matrix_num, ','))
                    {
                        if(matrix_num=="\n") break;
                        mtx[r][c]=std::stoll(matrix_num);
                        c++;
                    }
                    r++;c=0;
                }
                matrices.push_back(mtx);
                order.push_back('1');
            }
        }
        else continue;
    }
    return;
}