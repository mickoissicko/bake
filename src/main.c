#include "import/common/common.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* Bakefile;

    if (argc == 2 && strcmp(argv[1], "--gen-files") == 0)
    {
        Bakefile = fopen("Bakefile", "w");

        if (Bakefile != NULL)
        {
            fprintf(Bakefile, "! Bakefile\n");
            fprintf(Bakefile, "! ...\n");
            fprintf(Bakefile, "\n");
            fprintf(Bakefile, "!main{\n");
            fprintf(Bakefile, "    >echo 'Hello world';");
            fprintf(Bakefile, "}\n");
            fprintf(Bakefile, "\n");
            fprintf(Bakefile, "!serve{\n");
            fprintf(Bakefile, "    >echo 'Exiting now...';\n");
            fprintf(Bakefile, "}\n");

            fclose(Bakefile);

            return 0;
        }

        else
        {
            printf("Error creating Bakefile\n");
            return 1;
        }
    }

    else if (argc > 1)
    {
        printf("Unrecognised argument\n");
        return 1;
    }

    RunChecks();   // run checks to see if bake exists
                   //
    VerifyFile();  // call verifyfile to read and verify file
    Oven();        // finally, parse it

    return 0;
}
