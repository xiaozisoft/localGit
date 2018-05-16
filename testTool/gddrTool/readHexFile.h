#pragma once
#include <array>
#include <vector>
#include <fstream>

#define DefaultInitFilePath     (_T("./init_mem.dat"))
#define RegFilePath     (_T("./regWrite.dat"))

class readHexFile
{
public:
    readHexFile(std::string fileName);
    ~readHexFile();

    void readInitData();

public:
    std::vector<std::array <unsigned int, 3>> initData;
    std::ifstream fin;
};

