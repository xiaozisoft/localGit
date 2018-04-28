#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include "CbyteStream.h"
#include "CinputType.h"


class CwriteDdrRegInput
{
public:
    CwriteDdrRegInput();
    ~CwriteDdrRegInput();

    int setType(int t);
    int setBroadCast();
    int setUnicast();
    int setLowFlagReg();
    int clearLowFlagReg();


    int setChipAddr(int addr);
    int setRegAddr(unsigned int addr);
    int setData(unsigned int data);

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
    std::array<CbyteStream, 4> regData;

    std::array<unsigned char, 14> buffer;

};

