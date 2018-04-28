#include "stdafx.h"
#include "CpackageHead.h"
#include <string>

CpackageHead::CpackageHead(HeadType t)
{
    switch (t)
    {
    case Request:
        head.push_back(0x55);
        head.push_back(0xaa);
        break;
    case Responce:
        head.push_back(0xaa);
        head.push_back(0x55);
        break;
    default:
        break;
    }
    type = t;

    version = 1;
}

CpackageHead::CpackageHead(std::string h)
{
    if (h.size() > 4)
    {
        unsigned char tmp = 0;
        const char *p = h.c_str();
    }
    else
    {
        type = Unknow;
    }

}



CpackageHead::~CpackageHead()
{
}
