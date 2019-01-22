// modeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "crc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void test1Crc5(void)
{
    unsigned char test[] = { 0x08, 0xe0 };
    unsigned char crc1 = 0;
    unsigned char crcSecond = 0;

    crc1 = CRC5(test, 11);
    crcSecond = crc5usb(test, 2);

    printf("crc1 %x rc2 %x", crc1, crcSecond);
    _tsystem(_T("PAUSE"));
}

static int getInputNum(std::string input)
{
    std::string test = "20-0:1234";
    std::string tmpString;

    std::size_t a = test.find(':');

    if(a == std::string::npos)
    { 
        return 1;
    }

    std::string first = test.substr(0, a);
    std::string second = test.substr(a + 1, test.size());

    int tmp = 0;
    std::string tmpf;
    std::string tmps;

    a = first.find("-");
    if (a == std::string::npos)
    {
        tmp = std::stoi(test.substr(0, a), nullptr, 10);
    }
    else
    {
        tmpf = first.substr(0, a);
        tmps = first.substr(a + 1, first.size());
    }

    std::cout << first << ":::" << second << std::endl;

    return 0;
}

static int intain() {
    //用于存放分割后的字符串 
    std::vector<std::string> res;
    //待分割的字符串，含有很多空格 
    std::string word = "20-0:1234 31-21:1234";
    //暂存从word中读取的字符串 
    std::string result;
    //将字符串读到input中 
    std::stringstream input(word);
    //依次输出到result中，并存入res中 
    while (input >> result)
        res.push_back(result);
    //输出res 
    for (int i = 0; i < res.size(); i++) {
       std::cout << res[i] << std::endl;
    }
    return 0;
}

int main()
{
    getInputNum("a");

    return 0;
}

