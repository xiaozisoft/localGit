#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include "CbyteStream.h"
#include "CinputType.h"

class CreadDdrRegInput
{
public:
    CreadDdrRegInput();
    ~CreadDdrRegInput();

    int setType(int t);
    int setBroadCast();
    int setUnicast();
    int setLowFlagReg();
    int clearLowFlagReg();


    int setChipAddr(int addr);
    int setRegAddr(unsigned int addr);

    int calculateCrc();

    unsigned char * bufferSrc();
    int bufferSize();

    int printOut();
private:
    std::array<CbyteStream, 2> head;
    std::array<CbyteStream, 2> tailcrc;

    CinputType type;
    CbyteStream chipAddr;
    std::array<CbyteStream, 4> regAddr;

    std::array<unsigned char, 10> buffer;
};

