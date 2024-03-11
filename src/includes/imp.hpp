#pragma once

#ifndef MAIN_HPP
    #define MAIN_HPP
#endif

#include <string>

namespace defs {
    typedef std::ifstream isf;
    typedef std::ofstream osf;
    typedef std::string str;
}

void Cook(const std::string & command);
