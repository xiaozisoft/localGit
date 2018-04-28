#include "stdafx.h"
#include <string>

static int getCharValue(char a)
{
    if (a >= '0' && a <= '9')
    {
        return a - '0';
    }

    if (a >= 'a' && a <= 'f')
    {
        return a - 'a' + 10;
    }

    return 0;
}

unsigned int hexStringToUint(std::string dataHex)
{
    std::string tmp;
    if (dataHex.find(("0x")) == 0)
    {
        if (dataHex.size() > 10)
        {
            return 1;
        }
        tmp = dataHex.substr(2);
    }
    else
    {
        if (dataHex.size() > 8)
        {
            return 2;
        }
        tmp = dataHex;
    }

    unsigned int data = 0;

    for (auto a : tmp)
    {
        data = 16 * data + getCharValue(a);
    }

    return data;
}

std::string uintToHexString(unsigned int data)
{
    std::string tmp;

    tmp = std::to_string(data);

    return "0x" + tmp;
}