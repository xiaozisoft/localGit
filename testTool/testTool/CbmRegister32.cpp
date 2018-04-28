#include "stdafx.h"
#include "CbmRegister32.h"
#include <iostream>

CbmRegister32::CbmRegister32()
{
    r.reset();
    debugFlag = false;
}


CbmRegister32::~CbmRegister32()
{
}

int CbmRegister32::set(const unsigned int value)
{
    unsigned int tmpVal = value;

    for (size_t i = 0; i < r.size(); i++)
    {
        r[i] = tmpVal & 0x1;
        tmpVal >>= 1;
    }
    return 0;
}

int CbmRegister32::set(const unsigned int start, const unsigned int end, const unsigned int value)
{
    if (start > 31 || end < 0 || start > end)
    {
        return 1;
    }

    unsigned int tmpVal = value;

    for (unsigned int i = start; i <= end; i++)
    {
        r[i] = tmpVal & 0x1;
        tmpVal >>= 1;
    }

    if (debugFlag)
    {
        std::cout << "register write over: " << r.to_string() << std::endl;
    }

    return 0;
}

int CbmRegister32::get(unsigned int *value)
{
    unsigned int tmpValue = 0;

    for (unsigned int i = 31; i >= 0; i--)
    {
        tmpValue |= (r[i] ? 1 : 0);
        tmpValue <<= 1;
    }

    *value = tmpValue;
    return 0;
}

int CbmRegister32::get(const unsigned int start, const unsigned int end, unsigned int *value)
{
    if (start > 31 || end < 0 || start > end)
    {
        return 1;
    }

    unsigned int tmpValue = 0;

    for (unsigned int i = end; i >= start; i--)
    {
        tmpValue |= (r[i] ? 1 : 0);
        tmpValue <<= 1;
    }

    if (debugFlag)
    {
        std::cout << "register read over: " << tmpValue << std::endl;
    }

    *value = tmpValue;

    return 0;
}

int CbmRegister32::read(void)
{
    return 0;
}

int CbmRegister32::write(void)
{
    return 0;
}

void CbmRegister32::enableDebug()
{
    debugFlag = true;
}

void CbmRegister32::disableDebug()
{
    debugFlag = false;
}