#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <bits/stdc++.h>
#include "matrix.h"

namespace input
{
    bool checkValid(std::string &line);
    bool checkMatrixValues(std::string line);
    bool checkMatrixDimensions(std::string line);
    FILE* parser(int argc, char** argv, std::vector<char> &args,char &optFlag);
    void fileline_handler(std::vector<std::vector<std::vector<long long>>> &matrices, std::vector<long long> &scalars, std::vector<char> &order, FILE* fp);
}

#endif