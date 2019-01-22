#include "stdafx.h"
#include "readHexFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include "tool.h"


readHexFile::readHexFile(std::string fileName)
{
    fin.open(fileName);
}


readHexFile::~readHexFile()
{
    fin.close();
}

void readHexFile::readInitData()
{
    if (fin)
    {
        std::string s;
        int testp = 0;
        while (std::getline(fin, s))
        {
            std::string baseTmp;
            std::string offsetTmp;
            std::string valueTmp;
            std::array<unsigned int, 3> tmpUnit;
            //[PHY] zzz polling addr = 0x730, data = 0x1, bit = 31
            //[PHY] zzz write addr = 0x4, data = 0x10000000
            testp = s.find("=");

            baseTmp = s.substr(0, 1);
            offsetTmp = s.substr(2, 4);
            valueTmp = s.substr(7, 8);

            tmpUnit[0] = hexStringToUint(baseTmp);
            tmpUnit[1] = hexStringToUint(offsetTmp);
            tmpUnit[2] = hexStringToUint(valueTmp);

            initData.push_back(tmpUnit);
            std::cout << "Read from file: " << s << std::endl;
        }
    }
    return;
}
