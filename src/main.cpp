#include <iostream>
#include <fstream>

namespace defs{
    typedef std::ifstream isf;
    typedef std::ofstream osf;
}

int main()
{
    defs::isf BakeFile("Cook.bake");



    BakeFile.close();

    return 0;
}
