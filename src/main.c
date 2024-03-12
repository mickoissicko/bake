#include "common/common.h"

int main(int argc, char *argv[])
{
    Yaml(argc, argv);   // check if the user passed '-cfg' as argument
                        //
    RunChecks();        // run checks to see if bake exists
                        //
    VerifyFile();       // call verifyfile to read and verify file
    Oven();             // finally, parse it

    return 0;
}
