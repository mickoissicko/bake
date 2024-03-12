#pragma once

#ifndef COMMON_HPP
    #define COMMON_HPP
#endif

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>

namespace defs{
    typedef std::ifstream isf;
    typedef std::ofstream osf;
}

std::string ThrowVal(const std::string &value);

void VerifyFile();
void Oven();

void Yaml(int argc, char *argv[]);
void Cook(const std::string &command);
