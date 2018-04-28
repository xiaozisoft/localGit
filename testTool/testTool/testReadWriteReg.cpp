#include "stdafx.h"
#include "testReadWriteReg.h"
#include "Communication.h"
#include "CreadDdrRegRespoce.h"
#include "testInitConf.h"
#include "CwriteDdrRegInput.h"
#include "CreadDdrRegInput.h"
#include "CreadDdrRegRespoce.h"
#include "CwriteDdrDataInput.h"
#include "CreadDdrDataResponce.h"
#include "CreadDdrDataInput.h"

int testInit(Communication &c)
{
    unsigned char setInactive[] = { 0x55, 0xaa, 0x2b, 0x07, 0x00, 0x00, 0x08 };
    unsigned char setAddr[] = { 0x55, 0xaa, 0x20, 0x07, 0x00, 0x00, 0x11 };
    int ret = 0;

    ret = c.config(115200);
    if (ret != 0)
    {
        std::cout << "config error" << std::endl;
    }
    ret = c.writeData((const TCHAR*)setInactive, sizeof(setInactive));
    if (ret != 0)
    {
        std::cout << "writeData setInactive error" << std::endl;
    }

    ret = c.writeData((const TCHAR*)setAddr, sizeof(setAddr));
    if (ret != 0)
    {
        std::cout << "writeData setAddr error" << std::endl;
    }

    return 0;
}

int testOneReg(Communication &c)
{
    int ret = 0;
    unsigned char ctrlRegWrite[] = { 0x55, 0xaa, 0x31, 0x00, 0x00, 0x00, 0x00, 0x20, 0x34, 0x28, 0x56, 0x92, 0xe5, 0xce };
    ret = c.writeData((const TCHAR*)ctrlRegWrite, sizeof(ctrlRegWrite));

    unsigned char ctrlRegRead[] = { 0x55, 0xaa, 0x61, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0xca};
    c.writeData((const TCHAR*)ctrlRegRead, sizeof(ctrlRegRead));

    unsigned char ctrlRegReadBack[] = {0xaa, 0x55, 0x18, 0x00, 0x34, 0x28, 0x56, 0x92, 0xd7, 0x4b};

    CreadDdrRegResponce rdrr;
    int readLeng = rdrr.bufferSize();
    c.readData((TCHAR*)rdrr.bufferSrc(), &readLeng);

    rdrr.format();
    rdrr.printOut();
    if (rdrr.checkResponceCrc())
    {
        std::cout << "error crc" << std::endl;
    }

    return 0;
}

int testAllReg(Communication &c)
{
    return 0;
}

#define CHECK

int initFlow(Communication &c)
{
    CwriteDdrRegInput wdri;
    CreadDdrRegInput rdri;
    CreadDdrRegResponce rdrr;

    Rwe tmpCase;
    unsigned int regAddr = 0;
    unsigned int regData = 0;
    int readLength = 0;

    wdri.setType(3);
    wdri.setUnicast();
    wdri.setLowFlagReg();
    wdri.setChipAddr(0);

    rdri.setType(6);
    rdri.setUnicast();
    rdri.setLowFlagReg();
    rdri.setChipAddr(0);


    for (size_t i = 0; i < getSize(); i++)
    {
        //if ((i == (getSize() - 1)))
        //{
        //    Sleep(1);
        //}
        tmpCase = initDataFlow[i];
        if (tmpCase.baseAddr)
        {
            regAddr = 0x0002000;
        }
        else
        {
            regAddr = 0x0000000;
        }

        regAddr += tmpCase.offsetAddr;
        regData = tmpCase.data;

        wdri.setRegAddr(regAddr);
        wdri.setData(regData);
        wdri.calculateCrc();
        wdri.printOut();


        c.writeData((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
#ifdef CHECK
        rdri.setRegAddr(regAddr);
        rdri.calculateCrc();
        rdri.printOut();
        c.writeData((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());

        readLength = rdrr.bufferSize();
        c.readData((TCHAR *)rdrr.bufferSrc(), &readLength);

        rdrr.format();
        if (rdrr.checkResponceHead())
        {
            std::cout << "checkResponceHead error" << std::endl;
        }
        if (rdrr.checkResponceCrc())
        {
            std::cout << "checkResponceCrc error" << std::endl;
        }
        if (rdrr.checkMagicNum1())
        {
            std::cout << "checkMagicNum1 error" << std::endl;
        }
        rdrr.printOut();
#endif
    }

    return 0;
}

int readOneReg(Communication &c, unsigned int addr)
{
    unsigned int regAddr = 0;
    unsigned int regData = 0;
    int readLength = 0;
    CreadDdrRegInput rdri;
    CreadDdrRegResponce rdrr;

    regAddr = addr;

    rdri.setType(6);
    rdri.setUnicast();
    rdri.setLowFlagReg();
    rdri.setChipAddr(0);
    rdri.setRegAddr(regAddr);
    rdri.calculateCrc();
    rdri.printOut();
    c.writeData((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());

    readLength = rdrr.bufferSize();
    c.readData((TCHAR *)rdrr.bufferSrc(), &readLength);

    rdrr.format();
    if (rdrr.checkResponceHead())
    {
        std::cout << "checkResponceHead error" << std::endl;
    }
    if (rdrr.checkResponceCrc())
    {
        std::cout << "checkResponceCrc error" << std::endl;
    }
    if (rdrr.checkMagicNum1())
    {
        std::cout << "checkMagicNum1 error" << std::endl;
    }
    rdrr.printOut();
    return 0;
}

int writeOneReg(Communication &c, unsigned int addr, unsigned int data)
{
    CwriteDdrRegInput wdri;
    wdri.setType(3);
    wdri.setUnicast();
    wdri.setLowFlagReg();
    wdri.setChipAddr(0);

    wdri.setRegAddr(addr);
    wdri.setData(data);
    wdri.calculateCrc();
    wdri.printOut();

    c.writeData((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
    return 0;
}

int writeDdrData(Communication &c, unsigned int ad)
{
    CwriteDdrDataInput wddi;

    int addrTest = 0x0000;

    if (ad)
    {
        addrTest = ad;
    }

    unsigned char ddrIndata[] = { \
        0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, \
        0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, \
        0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x16, \
        0x17, 0x17, 0x17, 0x17, 0x18, 0x18, 0x18, 0x18, \
        0x21, 0x21, 0x21, 0x21, 0x22, 0x22, 0x22, 0x22, \
        0x23, 0x23, 0x23, 0x23, 0x24, 0x24, 0x24, 0x24, \
        0x25, 0x25, 0x25, 0x25, 0x26, 0x26, 0x26, 0x26, \
        0x27, 0x27, 0x27, 0x27, 0x28, 0x28, 0x28, 0x28};
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        //0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, \
        //0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
        //0x13, 0x52, 0x40, 0x85, 0x8e, 0x0b, 0x12, 0x58, \
        //0x07, 0x65, 0xa0, 0x94, 0xa1, 0xad, 0x71, 0x45, \
        //0x5e, 0xb1, 0x3b, 0x0d, 0x7e, 0x88, 0xbb, 0x28, \
        //0xd8, 0x78, 0x9c, 0x15, 0x44, 0x68, 0x56, 0xb1, \
        //0xf0, 0xd2, 0x11, 0xbc, 0xcf, 0x01, 0x74, 0x08, \
        //0xe3, 0xc9, 0xa2, 0x5a, 0xb6, 0x9e, 0x00, 0xa5, \
        //0xab, 0xa4, 0x21, 0x1d, 0x5c, 0x50, 0xa2, 0x30, \
        //0x04, 0xeb, 0x14, 0xcb, 0xd8, 0xe3, 0xca, 0x35 };

    wddi.setType(3);
    wddi.setUnicast();
    wddi.clearLowFlagReg();
    wddi.setChipAddr(0);
    wddi.setDdrAddr(addrTest);
    wddi.setData(ddrIndata, sizeof(ddrIndata) / sizeof(ddrIndata[0]));
    wddi.calculateCrc();
    wddi.printOut();

    c.writeData((const TCHAR*)wddi.bufferSrc(), wddi.bufferSize());

    return 0;
}

int readDdrData(Communication &c, unsigned int ad)
{
    CreadDdrDataInput rddi;
    CreadDdrDataResponce rddr;

    unsigned int addrTest = 0x0000;
    int readLength = 0;

    if (ad)
    {
        addrTest = ad;
    }

    rddi.setType(6);
    rddi.setUnicast();
    rddi.clearLowFlagReg();
    rddi.setChipAddr(0);
    rddi.setDdrAddr(addrTest);
    rddi.calculateCrc();
    rddi.printOut();

    c.writeData((const TCHAR*)rddi.bufferSrc(), rddi.bufferSize());
    std::cout << "read data:" << std::endl;
    readLength = rddr.bufferSize();
    c.readData((TCHAR *)rddr.bufferSrc(), &readLength);
    rddr.format();
    if (rddr.checkResponceHead())
    {
        std::cout << "checkResponceHead error" << std::endl;
    }
    if (rddr.checkResponceCrc())
    {
        std::cout << "checkResponceCrc error" << std::endl;
    }
    if (rddr.checkMagicNum1())
    {
        std::cout << "checkMagicNum1 error" << std::endl;
    }
    rddr.printOut();

    return 0;
}

