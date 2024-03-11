#include <iostream>
#include <string>

void Cook(const std::string & command)
{
    int result = std::system(command.c_str());

    if (result == 1)
    {
        std::cerr << "Error!" << std::endl
                  << "Exception at: " << std::endl
                  << result << std::endl;
    }
}
