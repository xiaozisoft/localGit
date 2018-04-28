#include "stdafx.h"
#include "CinputType.h"


CinputType::CinputType()
{
}


CinputType::~CinputType()
{
}

//type:bit7~4 
int CinputType::setType(int t)
{
    set(4, 7, t);
    return 0;
}

// all:bit3
int CinputType::setBroadcast()
{
    set(3, 3, 1);
    return 0;
}

int CinputType::setUnicast()
{
    set(3, 3, 0);
    return 0;
}

// all:bit2~0
int CinputType::setLowBit()
{
    set(0, 2, 1);
    return 0;
}

int CinputType::clearLowBit()
{
    set(0, 2, 0);
    return 0;
}