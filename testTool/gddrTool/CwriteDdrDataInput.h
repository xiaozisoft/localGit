#pragma once

#include <array>
#include <string>
#include "CbyteStream.h"
#include "CinputType.h"
#include "Ccrc.h"


class CwriteDdrDataInput
{
public:
    CwriteDdrDataInput();
    //CwriteDdrDataInput(std::string a);
    ~CwriteDdrDataInput();

    int setType(int t);
    int setBroadCast();
    int setUnicast();
    int setLowFlagReg();
    int clearLowFlagReg();


    int setChipAddr(int addr);
    int setDdrAddr(unsigned int addr);
    int setData(unsigned char *data, unsigned int dataLength);

    int calculateCrc();

    unsigned char * bufferSrc();
    int bufferSize();

    std::string getDataString();

private:
    std::array<CbyteStream, 2> head;
    std::array<CbyteStream, 2> tailCrc;

    CinputType type;
    CbyteStream chipAddr;
    std::array<CbyteStream, 4> ddrAddr;
    std::array<CbyteStream, 64> ddrWdata;

    std::array<unsigned char, 74> buffer;

};

