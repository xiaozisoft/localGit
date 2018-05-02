#pragma once
#include <array>
#include "CinputType.h"
#include "CbyteStream.h"
#include "Ccrc.h"
class CreadDdrRegResponce
{
public:
    CreadDdrRegResponce();
    ~CreadDdrRegResponce();

    int checkResponceHead();
    int checkResponceCrc();

    int checkMagicNum1();

    int getChipAddr();
    unsigned int getRegData();

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
    std::array<CbyteStream, 4> regData;

    unsigned char buffer[10];
};

