#pragma once
#include <array>
#include <vector>
#include <fstream>

#define DefaultDdrDataFilePath     (_T("./ddrData.dat"))
#define DivideFlag              (" ")

class readDdrDataFile
{
public:
    readDdrDataFile();
    ~readDdrDataFile();

    static std::array<unsigned char, 64> ddrInData;

    void readDdrDataInput();

public:
    std::ifstream fin;
};