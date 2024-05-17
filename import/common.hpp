#ifndef COMMON_HPP
    #define COMMON_HPP
#endif

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>

void VerifyFile();
void RunChecks();
void Oven();
std::string ThrowVal(const std::string &value);
void Cook(const std::string &command);

namespace defs
{
    typedef std::string str;
    typedef std::ifstream isf;
    typedef std::ofstream osf;
}

