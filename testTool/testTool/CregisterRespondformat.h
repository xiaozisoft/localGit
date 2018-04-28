#pragma once

#include <array>
#include"CbyteStream.h"
#include <string>


class CregisterRespondformat
{
public:
    CregisterRespondformat();
    ~CregisterRespondformat();


private:
    std::array<CbyteStream, 2> head;
    std::array<CbyteStream, 2> tailcrc;

    CbyteStream byte2;
    CbyteStream byte3;
    std::array<CbyteStream, 4> regData;
    CbyteStream chipAddr;
    CbyteStream regAddr;
};

