#pragma once

#ifndef DEFS_HPP
    #define DEFS_HPP
#endif

#include <fstream>
#include <string>

void Cook(const std::string & command);
void Yaml(int argc, char *argv[]);

std::string ThrowVal(const std::string & value);

namespace defs{
    typedef std::ifstream isf;
    typedef std::ofstream osf;
}
