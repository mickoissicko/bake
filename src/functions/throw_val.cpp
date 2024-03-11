#include <string>
#include <map>

std::string ThrowVal(const std::string & value)
{
    std::map<std::string, std::string> Vars;

    auto it = Vars.find(value);
    if (it != Vars.end())
    {
        return it -> second;
    }

    return "";
}
