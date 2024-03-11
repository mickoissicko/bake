#include "../includes/defs.hpp"

#include <iostream>

void Oven()
{
    bool ShouldExecute = false;

    std::string Line;

    defs::isf BakeFile("Bakefile");

    if (!BakeFile.is_open())
    {
        std::cerr << "No files?" << std::endl;
        return;
    }

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && !(Line.find("!--") == 0))
        {
            if (
                (Line.find("!cook{") != std::string::npos ||
                 Line.find("!main{") != std::string::npos ||
                 Line.find("!bake{") != std::string::npos ||
                 Line.find("!serve{") != std::string::npos) &&
                Line.find("{") != std::string::npos)
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

                if (start != std::string::npos && end != std::string::npos && start < end)
                {
                    std::string command = Line.substr(start + 1, end - start - 1);

                    size_t VarStart = command.find("[");
                    size_t VarTerminate = command.find("]");

                    while (VarStart != std::string::npos && VarTerminate != std::string::npos)
                    {
                        std::string varName = command.substr(VarStart + 1, VarTerminate - VarStart - 1);
                        std::string varValue = ThrowVal(varName);
                        command.replace(VarStart, VarTerminate - VarStart + 1, varValue);

                        VarStart = command.find("[");
                        VarTerminate = command.find("]");
                    }

                    Cook(command);
                }
            }
        }
    }

    BakeFile.close();
}
