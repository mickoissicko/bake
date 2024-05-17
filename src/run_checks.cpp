#include "../import/common.hpp"

using namespace defs;

void RunChecks()
{
    defs::isf BakeFile("Bakefile");
    
    if (!(BakeFile.is_open()))
    {
        std::cerr << "No files?" << std::endl;
        exit(1);
    }

    BakeFile.close();
}
