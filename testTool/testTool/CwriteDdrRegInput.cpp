#include "stdafx.h"
#include "CwriteDdrRegInput.h"
#include "Ccrc.h"


CwriteDdrRegInput::CwriteDdrRegInput()
{
    head[0].set(0x55);
    head[1].set(0xaa);
    buffer[0] = 0x55;
    buffer[1] = 0xaa;
}


CwriteDdrRegInput::~CwriteDdrRegInput()
{
}

int CwriteDdrRegInput::setType(int t)
{
    unsigned char tmp = 0;
    type.set(4, 7, t);
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrRegInput::setBroadCast()
{
    unsigned char tmp = 0;
    type.setBroadcast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrRegInput::setUnicast()
{
    unsigned char tmp = 0;
    type.setUnicast();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrRegInput::setLowFlagReg()
{
    unsigned char tmp = 0;
    type.setLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}

int CwriteDdrRegInput::clearLowFlagReg()
{
    unsigned char tmp = 0;
    type.clearLowBit();
    type.get(&tmp);
    buffer[2] = tmp;
    return 0;
}


int CwriteDdrRegInput::setChipAddr(int addr)
{
    unsigned char tmp = 0;
    chipAddr.set(0, 4, addr);
    chipAddr.get(&tmp);
    buffer[3] = tmp;
    return 0;
}

int CwriteDdrRegInput::setRegAddr(unsigned int addr)
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

int CwriteDdrRegInput::setData(unsigned int data)
{
    unsigned char tmp = 0;

    regData[0].set(data >> 24);
    regData[1].set(data >> 16);
    regData[2].set(data >> 8);
    regData[3].set(data);

    regData[0].get(&tmp);
    buffer[8] = tmp;
    regData[1].get(&tmp);
    buffer[9] = tmp;
    regData[2].get(&tmp);
    buffer[10] = tmp;
    regData[3].get(&tmp);
    buffer[11] = tmp;

    return 0;
}

int CwriteDdrRegInput::calculateCrc()
{
    uint16_t crcResult = 0;
    //crcResult = CRC16(buffer.data(), 12);
    crcResult = CRC16((uint8_t*)(buffer.data()) + 2, buffer.size() - 4);

    buffer[12] = (crcResult >> 8) & 0xff;
    buffer[13] = crcResult & 0xff;

    return 0;
}

unsigned char * CwriteDdrRegInput::bufferSrc()
{
    return buffer.data();
}

int CwriteDdrRegInput::bufferSize()
{
    return buffer.size();
}


int CwriteDdrRegInput::printOut()
{
    for (auto a : buffer)
    {
        int tmp = a;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << tmp << ' ';
    }

    std::cout << std::endl;
    return 0;
}

