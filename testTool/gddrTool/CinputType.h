#pragma once
#include "CbyteStream.h"
class CinputType :
    public CbyteStream
{
public:
    CinputType();
    ~CinputType();

    int setType(int t);
    int setBroadcast();
    int setUnicast();
    int setLowBit();
    int clearLowBit();
private:

};

