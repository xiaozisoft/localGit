#include "stdafx.h"
#include "CreadDdrRegRespoce.h"
#include <iostream>
#include <iomanip>
#include <sstream>


CreadDdrRegResponce::CreadDdrRegResponce()
{
    memset(buffer, 0, sizeof(buffer));
}


CreadDdrRegResponce::~CreadDdrRegResponce()
{
}

int CreadDdrRegResponce::checkResponceHead()
{
    unsigned char tmp = 0;
    head[0].get(&tmp);
    if (tmp != 0xaa)
    {
        return 1;
    }
    head[1].get(&tmp);
    if (tmp != 0x55)
    {
        return 1;
    }

    return 0;
}
int CreadDdrRegResponce::checkResponceCrc()
{
    uint16_t crcResult = 0;
    unsigned char tmp = 0;
    crcResult = CRC16(buffer + 2, bufferSize() - 4);

    tailcrc[0].get(&tmp);
    if (tmp != (tmp & (crcResult >> 8)))
    {
        return 1;
    }

    tailcrc[1].get(&tmp);
    if (tmp != (tmp & crcResult))
    {
        return 1;
    }

    return 0;
}

int CreadDdrRegResponce::checkMagicNum1()
{
    unsigned char tmp = 0;
    magicNum1.get(&tmp);
    if (tmp != 0x18)
    {
        return 1;
    }

    return 0;
}

int CreadDdrRegResponce::getChipAddr()
{
    unsigned char tmp = 0;
    chipAddr.get(0, 4, &tmp);

    return tmp;
}

unsigned int CreadDdrRegResponce::getRegData()
{
    unsigned int tmp = 0;
    unsigned char t = 0;

    for (size_t i = 0; i < regData.size(); i++ )
    {
        regData[i].get(&t);
        tmp |= t;
        if (i < regData.size() - 1)
        {
            tmp <<= 8;
        }
    }

    return tmp;
}

unsigned char * CreadDdrRegResponce::bufferSrc()
{
    return buffer;
}

int CreadDdrRegResponce::bufferSize()
{
    return sizeof(buffer);
}

int CreadDdrRegResponce::format()
{
    head[0].set(buffer[0]);
    head[1].set(buffer[1]);

    tailcrc[0].set(buffer[8]);
    tailcrc[1].set(buffer[9]);

    magicNum1.set(buffer[2]);
    chipAddr.set(0, 4, buffer[3] & 0x0f);
    regData[0].set(buffer[4]);
    regData[1].set(buffer[5]);
    regData[2].set(buffer[6]);
    regData[3].set(buffer[7]);

    return 0;
}

std::string CreadDdrRegResponce::getDataString()
{
    std::stringstream tmpSs;

    for (unsigned int i = 0; i < sizeof(buffer); i++)
    {
        int tmp = buffer[i];
        tmpSs << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    tmpSs << std::endl;

    tmpSs << "regData:" << std::hex << getRegData() << std::endl;

    std::string tmpStr = tmpSs.str();
    return tmpStr;
}
