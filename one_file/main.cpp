#include "common.hpp"

std::map<std::string, std::string> Vars;

using namespace defs;

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

void Oven()
{
    bool ShouldExecute = false;

    std::string Line;

    defs::isf BakeFile("Bakefile");

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && !(Line.find("!--") == 0))
        {
            if (
                (Line.find("!cook{") != str::npos   ||
                 Line.find("!main{") != str::npos   || // sussy
                 Line.find("!bake{") != str::npos   ||
                 Line.find("!serve{") != str::npos) &&
                Line.find("{") != str::npos)
            {
                ShouldExecute = true;
            }

            if (ShouldExecute && Line.find("}") == 0)
            {
                ShouldExecute = false;
            }

            if (ShouldExecute)
            {
                size_t start = Line.find(">");
                size_t end = Line.rfind(";");

                if (
                    start != str::npos &&
                    end   != str::npos &&
                    start < end
                )
                {
                    std::string command = Line.substr(start + 1, end - start - 1);

                    size_t VarStart = command.find("[");
                    size_t VarTerm = command.find("]");

                    while (VarStart != str::npos && VarTerm != str::npos)
                    {
                        std::string Var = command.substr(VarStart + 1, VarTerm - VarStart - 1);
                        std::string Val = ThrowVal(Var);
                        command.replace(VarStart, VarTerm - VarStart + 1, Val);

                        VarStart = command.find("[");
                        VarTerm = command.find("]");
                    }
                    Cook(command);
                }
            }
        }
    }

    BakeFile.close();
}

std::string ThrowVal(const std::string &value)
{
    auto it = Vars.find(value);
    
    if (it != Vars.end())
    {
        return it -> second;
    }

    return "";
}

void Cook(const std::string &command)
{
    int result = std::system(command.c_str());

    if (result == 1)
    {
        std::cerr << "Error!"
                  << std::endl
                  << "Exception at: "
                  << std::endl
                  << result << std::endl;
    }
}

void VerifyFile()
{
    defs::isf BakeFile("Bakefile");

    bool MainFound  = false;
    bool BakeFound  = false;
    bool CookFound  = false;
    bool ServeFound = false;
    bool InMain     = false;
    bool InBake     = false;
    bool InCook     = false;
    bool InServe    = false;

    std::string Line;

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && Line.find("!main{") != str::npos)
        {
            InMain = true;
        }
        else if (!(Line.empty()) && Line.find("!bake{") != str::npos)
        {
            InBake = true;
        }
        else if (!(Line.empty()) && Line.find("!cook{") != str::npos)
        {
            InCook = true;
        }
        else if (
            !(Line.empty()) && Line.find("!serve{") != str::npos ||
            Line.find("!serve{}") != str::npos
        )
        {
            InServe = true;
        }

        size_t BracePosition = Line.find_last_of('}');
        if (BracePosition != str::npos)
        {
            if (InMain)
            {
                InMain = false;
                MainFound = true;
            }
            else if (InBake)
            {
                InBake = false;
                BakeFound = true;
            }
            else if (InCook)
            {
                InCook = false;
                CookFound = true;
            }
            else if (InServe)
            {
                InServe = false;
                ServeFound = true;
            }
        }

        size_t AssignVar = Line.find(":");
        size_t VarStart = Line.find("[");
        size_t VarTerm = Line.find("]");

        if (AssignVar != str::npos && VarStart != str::npos && VarTerm != str::npos)
        {
            std::string Var = Line.substr(0, AssignVar);
            std::string Val = Line.substr(VarStart + 1, VarTerm - VarStart - 1);
            Vars[Var] = Val;
        }
    }

    BakeFile.close();

    if (!ServeFound)
    {
        std::cerr << "Missing required section to exit" << std::endl;

        exit(1);
    }

    else if (!(MainFound || CookFound || BakeFound))
    {
        std::cerr << "Missing required section to start" << std::endl;

        exit(1);
    }
}

void Yaml(int argc, char *argv[])
{
    using namespace std;

    if (argc > 1 && strcmp(argv[1], "-cfg") == 0)
    {
        defs::osf YamlCfg("chefs_choice.yml");

        YamlCfg << "# THIS FILE IS A PLACEHOLDER CURRENTLY AND HAS NO FUNCTION!"
                << endl
                << endl;

        YamlCfg << "# This file has been auto-generated by Bake"
                << endl
                << "# It contains preferences that you can customise"
                << endl
                << "# You can also change the name of the target Bakefile"
                << endl
                << endl
                << "# If you want to regenerate this file: run bake with '-cfg' argument"
                << endl
                << "# Remember: Bake is currently under development, so not all features might work!"
                << endl
                << endl
                << "# If you don't want to use the YAML file anymore, change it to false"
                << endl
                << "# You can also set 'BuildFromYaml' mode to 'True'"
                << endl
                << "# Setting BuildFromYaml to true will make it so that Bake bakes everything from here"
                << endl
                << endl
                << "Yaml: False"
                << endl
                << "BuildFromYaml: False"
                << endl
                << endl
                << "# This is the function where you can specify build commands"
                << endl
                << "[BuildFromYaml]"
                << endl
                << "  - del_file: 'rm -rf foo bar'"
                << endl
                << "  - spameggs: 'spam eggs'"
                << endl
                << endl
                << "# And this is the normal function if you are also using Bakefile"
                << endl
                << "# Also, the 'default' value means the default stored in the program, so:"
                << endl
                << "# Bakefile as name without an extension"
                << endl
                << endl
                << "# Remember to change 'default' to desired value"
                << endl
                << "# And you need to specify a drive letter (i.e. X:\\) if you're on Windows"
                << endl
                << "[Yaml]"
                << endl
                << "  - BakeFileName: default"
                << endl
                << "  - BakeFileExtension: default"
                << endl
                << "  - BakeFilePath: default"
                << endl;

        YamlCfg.close();

        exit(0);
    }
}
