#include "logger.h"

#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <ctime>

#include "exceptions.h"


LOGGER* LOGGER::logger = NULL;
std::fstream LOGGER::stlogfile;
std::string LOGGER::logfname = "outputLog.log";
LOGGER::LOGGER() {}
LOGGER* LOGGER::GetLogger()
{
    if (LOGGER::logger == NULL)
    {
        LOGGER::logger = new LOGGER();
        LOGGER::stlogfile.open( LOGGER::logfname, std::ios::out | std::ios::app);
    }
    return LOGGER::logger;
}

void LOGGER::deleteLogger()
{
    if (LOGGER::logger != NULL)
    {
        delete LOGGER::logger;
        LOGGER::logger = NULL;
        if (LOGGER::stlogfile.is_open())
        {
            LOGGER::stlogfile.close();
        }
    }
}