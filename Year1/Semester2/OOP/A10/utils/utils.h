

#pragma once

#include <string>

class Utils {

public:

    /**
     * Function that converts a number to a string
     * @param str String - the string to be converted
     * @return  int - the number
     */
    static int StringToNumber(const std::string &str);

    /**
     * Function that checks if a string is a number
     * @param str String - the string to be checked
     * @return bool - true if the string is a number, false otherwise
     */
    static bool IsNumber(const std::string &str);
};
