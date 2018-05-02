#pragma once
#include <array>
#include <string>
#include "CbyteStream.h"

class CreadDdrDataResponce
{
public:
    CreadDdrDataResponce();
    ~CreadDdrDataResponce();

    int checkResponceHead();
    int checkResponceCrc();

    int checkMagicNum1();

    int getChipAddr();

    unsigned char * bufferSrc();
    int bufferSize();

    int format();
    std::string getDataString();

private:
    bool errorNum;
    std::array<CbyteStream, 2> head;
    std::array<CbyteStream, 2> tailcrc;

    CbyteStream magicNum1;
    CbyteStream chipAddr;
    std::array<CbyteStream, 64> ddrData;

    unsigned char buffer[70];
};

