#include "stdafx.h"
#include "CreadDdrDataResponce.h"
#include <iostream>
#include <iomanip>
#include "Ccrc.h"


CreadDdrDataResponce::CreadDdrDataResponce()
{
    memset(buffer, 0, sizeof(buffer));
}


CreadDdrDataResponce::~CreadDdrDataResponce()
{
}

int CreadDdrDataResponce::checkResponceHead()
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
int CreadDdrDataResponce::checkResponceCrc()
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

int CreadDdrDataResponce::checkMagicNum1()
{
    unsigned char tmp = 0;
    magicNum1.get(&tmp);
    if (tmp != 0x08)
    {
        return 1;
    }

    return 0;
}

int CreadDdrDataResponce::getChipAddr()
{
    unsigned char tmp = 0;
    chipAddr.get(0, 4, &tmp);

    return tmp;
}

unsigned char * CreadDdrDataResponce::bufferSrc()
{
    return buffer;
}

int CreadDdrDataResponce::bufferSize()
{
    return sizeof(buffer);
}

int CreadDdrDataResponce::format()
{
    head[0].set(buffer[0]);
    head[1].set(buffer[1]);

    tailcrc[0].set(buffer[68]);
    tailcrc[1].set(buffer[69]);

    magicNum1.set(buffer[2]);
    chipAddr.set(0, 4, buffer[3] & 0x0f);

    for (size_t i = 0; i < ddrData.size(); i++)
    {
        ddrData[i].set(buffer[4 + i]);
    }

    return 0;
}

int CreadDdrDataResponce::printOut()
{
    for (unsigned int i = 0; i < sizeof(buffer); i++)
    {
        int tmp = buffer[i];
        std::cout << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    std::cout << std::endl;

    return 0;
}
