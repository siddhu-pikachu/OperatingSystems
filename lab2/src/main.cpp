#include "input.h"
#include <bits/stdc++.h>
#include <fstream>

#include "matrix.h"
#include "logger.h"
#include "exceptions.h"
#include "output.h"

using namespace std;

int main(int argc, char **argv)
{
    // std::cout<<"hello              ====================="<<std::endl;
    LOGGER *logger = NULL;
    if(argc==1 or argc==2)
    {
        std::cout<<argc<<std::endl;
        
        throw exceptions::invalid_arguments();
    }
    try
    {
        logger = LOGGER::GetLogger();

        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile << "Starting :) ------------------------------------------------------------------\n";
            LOGGER::stlogfile << "In main.cpp ...\n";
            LOGGER::stlogfile << "Fetching the arguments :) \n";
        }
        else
        {
            throw exceptions::file_notfound();
        }

        vector<char> args;
        char optFlag;

        FILE* fp;
        fp = input::parser(argc,argv,args,optFlag);
        if(fp==NULL)
        {
            throw exceptions::file_notfound();
        }

        vector<char> ord;
        vector<vector<vector<long long>>> matricesv;
        vector<long long> scalarsv;

        if(args.size()==0)
        {
            throw exceptions::no_arguments();
        }

        input::fileline_handler(matricesv,scalarsv,ord,fp);

        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile << "option received for operation: "<< optFlag << "\n";
            LOGGER::stlogfile << "Number of matrices involved in operation: "<<matricesv.size()<<"\n";
            LOGGER::stlogfile << "The matrices are: \n";
            for(auto mtrx : matricesv)
            {
                for(long long i=0;i<mtrx.size();i++)
                {
                    for(long long j=0;j<mtrx[0].size();j++)
                    {
                        LOGGER::stlogfile<<mtrx[i][j]<<" ";
                    }
                    LOGGER::stlogfile<<"\n";
                }
                LOGGER::stlogfile<<"\n";
            }
            for(auto sc : scalarsv)
            {
                LOGGER::stlogfile<<sc<<" ";
            }
            LOGGER::stlogfile<<"\n";
        }
        else
        {
            throw exceptions::file_notfound();
        }
        
 
        output::matrixEvaluation(matricesv,scalarsv,optFlag,ord);
    }
    catch(std::exception &ex)
    {
        // FILE *fp;
        // fp=fopen("final_output.txt","w");
        // fprintf(fp,"%s\n",ex.what());
        std::cout<<ex.what()<<std::endl;

        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile << ex.what() << " :( \n";
        }
        else
        {
            throw exceptions::file_notfound();
        }
    }

    if (LOGGER::stlogfile.is_open())
    {
        LOGGER::stlogfile << "Back to main.cpp (Successfully)...\n";
        LOGGER::stlogfile << "Exiting Successfully :) ------------------------------------------------------------------\n";
    }
    else
    {
        throw exceptions::file_notfound();
    }

    LOGGER::deleteLogger();

    return 0;
}