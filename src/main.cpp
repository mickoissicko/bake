#include "import/common/common.h"

#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--gen-files") == 0)
    {
        std::ofstream Bakef("Bakefile");

        if (Bakef.is_open())
        {
            Bakef << "! Bakefile" 
                  << std::endl
                  << "! ..." 
                  << std::endl
                  << std::endl
                  << "!main{"
                  << std::endl
                  << "    >echo 'Hello world!';"
                  << std::endl
                  << "}"
                  << std::endl
                  << std::endl
                  << "!serve{"
                  << std::endl
                  << "    >echo 'Exiting..';"
                  << std::endl
                  << "}"
                  << std::endl;

            Bakef.close();

            return 0;
        }

        else
        {
            std::cerr << "Unrecognised argument" << std::endl;
            return 1;
        }
    }

    else if (argc > 1)
    {
        std::cerr << "Unrecognised argument" << std::endl;
        return 1;
    }

    RunChecks();   // run checks to see if bake exists
                   //
    VerifyFile();  // call verifyfile to read and verify file
    Oven();        // finally, parse it

    return 0;
}
