#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "CwriteDdrDataInput.h"


CwriteDdrDataInput::CwriteDdrDataInput()
{
    head.at(1).set(0xaa);
    head.at(1).set(0x55);
    buffer[0] = 0x55;
    buffer[1] = 0xaa;
}


CwriteDdrDataInput::~CwriteDdrDataInput()
{
}

int CwriteDdrDataInput::setType(int t)
{
    unsigned char tmp = 0;
    type.set(4, 7, t);
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrDataInput::setBroadCast()
{
    unsigned char tmp = 0;
    type.setBroadcast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrDataInput::setUnicast()
{
    unsigned char tmp = 0;
    type.setUnicast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrDataInput::setLowFlagReg()
{
    unsigned char tmp = 0;
    type.setLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrDataInput::clearLowFlagReg()
{
    unsigned char tmp = 0;
    type.clearLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}


int CwriteDdrDataInput::setChipAddr(int addr)
{
    unsigned char tmp = 0;
    chipAddr.set(0, 4, addr);
    chipAddr.get(&tmp);
    buffer[3] = tmp;
    return 0;
}

int CwriteDdrDataInput::setDdrAddr(unsigned int addr)
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

int CwriteDdrDataInput::setData(unsigned char *pData, unsigned int dataLength)
{
    if (pData == NULL || dataLength > 512)
    {
        return 1;
    }

    int i = 0;
    for (auto &a : ddrWdata)
    {
        a.set(pData[i]);
        i++;
    }

    for (size_t j = 0;  j < ddrWdata.size();  j++)
    {
        buffer[8 + j] = pData[j];
    }

    return 0;
}

int CwriteDdrDataInput::calculateCrc()
{
    uint16_t crcResult = 0;
    //crcResult = CRC16(buffer.data(), 12);
    crcResult = CRC16((uint8_t*)(buffer.data()) + 2, (uint16_t)buffer.size() - 4);

    buffer[72] = (crcResult >> 8) & 0xff;
    buffer[73] = crcResult & 0xff;

    return 0;
}

unsigned char * CwriteDdrDataInput::bufferSrc()
{
    return buffer.data();
}

int CwriteDdrDataInput::bufferSize()
{
    return buffer.size();
}


int CwriteDdrDataInput::printOut()
{
    for (auto a : buffer)
    {
        int tmp = a;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    std::cout << std::endl;
    return 0;
}
