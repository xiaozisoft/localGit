#pragma once
#include <array>
#include <string>
#include "CbyteStream.h"
#include "CinputType.h"

class CreadDdrDataInput
{
public:
    CreadDdrDataInput();
    ~CreadDdrDataInput();

    int setType(int t);
    int setBroadCast();
    int setUnicast();
    int setLowFlagReg();
    int clearLowFlagReg();


    int setChipAddr(int addr);
    int setDdrAddr(unsigned int addr);

    int calculateCrc();

    unsigned char * bufferSrc();
    int bufferSize();

    std::string getDataString();
private:
    std::array<CbyteStream, 2> head;
    std::array<CbyteStream, 2> tailcrc;

    CinputType type;
    CbyteStream chipAddr;
    std::array<CbyteStream, 4> ddrAddr;

    std::array<unsigned char, 10> buffer;
};

