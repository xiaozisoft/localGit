#pragma once
#include "CbyteStream.h"


class Cpackage
{
public:
    Cpackage();
    ~Cpackage();

private:
    CbyteStream head[2];
    CbyteStream tailcrc[2];
};

