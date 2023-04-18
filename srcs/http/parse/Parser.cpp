#include "Parser.hpp"

std::vector<std::string>	Parser::split(std::string str, std::string delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delim.length());
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}

std::vector<std::string>	Parser::split(std::string str, char delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + 1);
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}

void	Parser::trim(std::string& str)
{
    // Trim leading spaces
    std::string::iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        ++it;
    }
    str.erase(str.begin(), it);

    // Trim trailing spaces
    it = str.end();
    while (it != str.begin() && std::isspace(*(it - 1))) {
        --it;
    }
    str.erase(it, str.end());
}

std::string Parser::toupper(std::string str)
{
    std::string result;

    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if ('a' <= *it && *it <= 'z')
            result += char(*it - 'a' + 'A');
        else
            result += *it;
    }
    return result;
}