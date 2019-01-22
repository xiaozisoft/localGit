#include "stdafx.h"
#include "executionFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include "tool.h"

executionFile::executionFile(std::string fileName)
{
    fin.open(fileName);
}


executionFile::~executionFile()
{
    fin.close();
}