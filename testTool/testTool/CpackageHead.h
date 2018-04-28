#pragma once

#include <string>
#include <vector>
#include <stdint.h>

class CpackageHead
{
public:
    typedef enum
    {
        Unknow = 0,
        Request,
        Responce,
    }HeadType;

    CpackageHead(HeadType t);
    CpackageHead(std::string h);
    ~CpackageHead();

    //bool isResponceHead();

private:
    HeadType type;
    std::vector<unsigned char> head;

    int version;
};

