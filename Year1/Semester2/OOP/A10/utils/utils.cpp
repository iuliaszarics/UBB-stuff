

#include "utils.h"

bool Utils::IsNumber(const std::string& str) {


    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
            return false;
    }

    return true;
}

int Utils::StringToNumber(const std::string& str) {

    int number = 0;

    for (int i = 0; i < str.length(); i++)
    {
        number = number * 10 + str[i] - '0';
    }

    return number;
}
