#include "stdafx.h"
#include "CreadDdrRegInput.h"
#include "Ccrc.h"


CreadDdrRegInput::CreadDdrRegInput()
{
    head[0].set(0x55);
    head[1].set(0xaa);
    buffer[0] = 0x55;
    buffer[1] = 0xaa;
}


CreadDdrRegInput::~CreadDdrRegInput()
{
}

int CreadDdrRegInput::setType(int t)
{
    unsigned char tmp = 0;
    type.set(4, 7, t);
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrRegInput::setBroadCast()
{
    unsigned char tmp = 0;
    type.setBroadcast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrRegInput::setUnicast()
{
    unsigned char tmp = 0;
    type.setUnicast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrRegInput::setLowFlagReg()
{
    unsigned char tmp = 0;
    type.setLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrRegInput::clearLowFlagReg()
{
    unsigned char tmp = 0;
    type.clearLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CreadDdrRegInput::setChipAddr(int addr)
{
    unsigned char tmp = 0;
    chipAddr.set(0, 4, addr);
    chipAddr.get(&tmp);
    buffer[3] = tmp;
    return 0;
}

int CreadDdrRegInput::setRegAddr(unsigned int addr)
{
    unsigned char tmp = 0;

    regAddr[0].set(addr >> 24);
    regAddr[1].set(addr >> 16);
    regAddr[2].set(addr >> 8);
    regAddr[3].set(addr);

    regAddr[0].get(&tmp);
    buffer[4] = tmp;
    regAddr[1].get(&tmp);
    buffer[5] = tmp;
    regAddr[2].get(&tmp);
    buffer[6] = tmp;
    regAddr[3].get(&tmp);
    buffer[7] = tmp;
    return 0;
}

int CreadDdrRegInput::calculateCrc()
{
    uint16_t crcResult = 0;

    crcResult = CRC16((uint8_t*)(buffer.data()) + 2, (uint16_t)buffer.size() - 4);

    buffer[8] = (crcResult >> 8) & 0xff;
    buffer[9] = crcResult & 0xff;

    return 0;
}

unsigned char * CreadDdrRegInput::bufferSrc()
{
    return buffer.data();
}

int CreadDdrRegInput::bufferSize()
{
    return buffer.size();
}


int CreadDdrRegInput::printOut()
{
    for (auto a : buffer)
    {
        int tmp = a;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    std::cout << std::endl;
    return 0;
}
