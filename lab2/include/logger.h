#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <fstream>

class LOGGER
{
    public:
    LOGGER();
    static LOGGER *logger;
    static std::string logfname;
    static std::fstream stlogfile;
    static LOGGER *GetLogger();
    static void deleteLogger();
};


#endif