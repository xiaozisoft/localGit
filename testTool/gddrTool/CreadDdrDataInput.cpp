#include "stdafx.h"
#include "CreadDdrDataInput.h"
#include "Ccrc.h"
#include <iostream>
#include <iomanip>
#include <sstream>

CreadDdrDataInput::CreadDdrDataInput()
{
    head[0].set(0x55);
    head[1].set(0xaa);
    buffer[0] = 0x55;
    buffer[1] = 0xaa;
}


CreadDdrDataInput::~CreadDdrDataInput()
{
}

int CreadDdrDataInput::setType(int t)
{
    unsigned char tmp = 0;
    type.set(4, 7, t);
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrDataInput::setBroadCast()
{
    unsigned char tmp = 0;
    type.setBroadcast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrDataInput::setUnicast()
{
    unsigned char tmp = 0;
    type.setUnicast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrDataInput::setLowFlagReg()
{
    unsigned char tmp = 0;
    type.setLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrDataInput::clearLowFlagReg()
{
    unsigned char tmp = 0;
    type.clearLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrDataInput::setChipAddr(int addr)
{
    unsigned char tmp = 0;
    chipAddr.set(0, 4, addr);
    chipAddr.get(&tmp);
    buffer[3] = tmp;
    return 0;
}

int CreadDdrDataInput::setDdrAddr(unsigned int addr)
{
    unsigned char tmp = 0;

    ddrAddr[0].set(addr >> 24);
    ddrAddr[1].set(addr >> 16);
    ddrAddr[2].set(addr >> 8);
    ddrAddr[3].set(addr);

    ddrAddr[0].get(&tmp);
    buffer[4] = tmp;
    ddrAddr[1].get(&tmp);
    buffer[5] = tmp;
    ddrAddr[2].get(&tmp);
    buffer[6] = tmp;
    ddrAddr[3].get(&tmp);
    buffer[7] = tmp;
    return 0;
}

int CreadDdrDataInput::calculateCrc()
{
    uint16_t crcResult = 0;

    crcResult = CRC16((uint8_t*)(buffer.data()) + 2, buffer.size() - 4);

    buffer[8] = (crcResult >> 8) & 0xff;
    buffer[9] = crcResult & 0xff;

    return 0;
}

unsigned char * CreadDdrDataInput::bufferSrc()
{
    return buffer.data();
}

int CreadDdrDataInput::bufferSize()
{
    return buffer.size();
}


std::string CreadDdrDataInput::getDataString()
{
    std::stringstream tmpSs;
    for (auto a : buffer)
    {
        int tmp = a;
        tmpSs << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    tmpSs << std::endl;

    std::string tmpStr = tmpSs.str();
    return tmpStr;
}
