#include "includes/defs.hpp"
#include "includes/modules.h"

#include <fstream>
#include <string>
#include <iostream>

void RunChecks(int argc, char* argv[])
{
    Yaml(argc, argv);

    defs::isf BakeFile("Bakefile");
    
    if (!(BakeFile.is_open()))
    {
        std::cerr << "No files?" << std::endl;
        exit(1);
    }

    BakeFile.close();

    VerifyFile();
    Oven();
}
