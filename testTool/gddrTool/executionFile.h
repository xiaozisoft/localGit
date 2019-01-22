#pragma once
#include <array>
#include <vector>
#include <fstream>

#define DefaultInitFilePath     (_T("./init_mem.dat"))
//#define RegFilePath     (_T("./regWrite.dat"))
#define RegFilePath     (_T("./text.txt"))
class executionFile
{
public:
    executionFile(std::string fileName);
    ~executionFile();

    //void readInitData();

public:
    std::vector<std::array <unsigned int, 3>> initData;
    std::ifstream fin;
};