#ifndef COMMON_HPP
    #define COMMON_HPP
#endif

#include <string>
#include <fstream>

void VerifyFile();
void RunChecks();
void Oven();
std::string ThrowVal(const std::string &value);
void Cook(const std::string &command);
