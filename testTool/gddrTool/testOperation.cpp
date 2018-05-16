#include "stdafx.h"
#include "CwriteDdrRegInput.h"
#include "CreadDdrRegInput.h"
#include "CreadDdrRegRespoce.h"
#include "CwriteDdrDataInput.h"
#include "CreadDdrDataResponce.h"
#include "CreadDdrDataInput.h"
#include "Serial.h"
#include "testInitConf.h"
#include "testData.h"
#include <tchar.h>
#include "readHexFile.h"

#define ReadTimeOut                 (10000)

static void writeLog(std::string log, CEdit &edit)
{
    CString logTmp;
    int nLength = edit.SendMessage(WM_GETTEXTLENGTH);
    logTmp.Format(log.data());
    logTmp += _T("\r\n");
    edit.SetSel(nLength, nLength);
    edit.ReplaceSel(logTmp);
}

int setAddrInit(CSerial &c, CEdit &edit)
{
    writeLog(std::string("Set addr!"), edit);

    unsigned char setInactive[] = { 0x55, 0xaa, 0x2b, 0x07, 0x00, 0x00, 0x08 };
    unsigned char setAddr[] = { 0x55, 0xaa, 0x20, 0x07, 0x00, 0x00, 0x11 };
    int ret = 0;

    ret = c.Write((const TCHAR*)setInactive, sizeof(setInactive));
    if (ret != 0)
    {
        writeLog(std::string("writeData setInactive error!"), edit);
    }

    ret = c.Write((const TCHAR*)setAddr, sizeof(setAddr));
    if (ret != 0)
    {
        writeLog(std::string("writeData setAddr error!"), edit);
    }

    writeLog(std::string("Set addr OK!"), edit);

    return 0;
}

int testOneReg(CSerial &c, CEdit &edit)
{
    writeLog(std::string("One ctrl reg read write test :"), edit);

    int ret = 0;
    unsigned char ctrlRegWrite[] = { 0x55, 0xaa, 0x31, 0x00, 0x00, 0x00, 0x00, 0x20, 0x34, 0x28, 0x56, 0x92, 0xe5, 0xce };
    ret = c.Write((const TCHAR*)ctrlRegWrite, sizeof(ctrlRegWrite));
    if (ret != 0)
    {
        writeLog(std::string("Write reg command send error!"), edit);
        return 1;
    }
    unsigned char ctrlRegRead[] = { 0x55, 0xaa, 0x61, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0xca };
    ret = c.Write((const TCHAR*)ctrlRegRead, sizeof(ctrlRegRead));
    if (ret != 0)
    {
        writeLog(std::string("Read reg command send error!"), edit);
        return 2;
    }

    unsigned char ctrlRegReadBack[] = { 0xaa, 0x55, 0x18, 0x00, 0x34, 0x28, 0x56, 0x92, 0xd7, 0x4b };

    CreadDdrRegResponce rdrr;
    DWORD readLeng = 0;
    ret = c.Read((TCHAR*)rdrr.bufferSrc(), rdrr.bufferSize(), &readLeng);
    if (ret != 0)
    {
        writeLog(std::string("Read reg command receive error!"), edit);
        return 3;
    }

    rdrr.format();

    writeLog(rdrr.getDataString(), edit);

    if (rdrr.checkResponceCrc())
    {
        writeLog(std::string("Read reg command receive CRC error!"), edit);
        return 4;
    }

    writeLog(std::string("One ctrl reg read write test OK!:"), edit);
    return 0;
}

#define UseFileInit
#define CHECK

int initGddrDataFlow(CSerial &c, CEdit &edit)
{
    int ret = 0;
    readHexFile initHexFile(DefaultInitFilePath);
    CwriteDdrRegInput wdri;
    CreadDdrRegInput rdri;
    CreadDdrRegResponce rdrr;

    unsigned int regAddr = 0;
    unsigned int regData = 0;
    DWORD readLength = 0;

    wdri.setType(3);
    wdri.setUnicast();
    wdri.setLowFlagReg();
    wdri.setChipAddr(0);

    rdri.setType(6);
    rdri.setUnicast();
    rdri.setLowFlagReg();
    rdri.setChipAddr(0);
#ifdef UseFileInit
    std::array<unsigned int, 3> tmpCase;
    initHexFile.readInitData();
    for (size_t i = 0; i < initHexFile.initData.size(); i++)
    {
        tmpCase = initHexFile.initData[i];
        if (tmpCase[0])
        {
            regAddr = 0x0002000;
        }
        else
        {
            regAddr = 0x0000000;
        }

        regAddr += tmpCase[1];
        regData = tmpCase[2];

        wdri.setRegAddr(regAddr);
        wdri.setData(regData);
        wdri.calculateCrc();

        writeLog(wdri.getDataString(), edit);


        ret = c.Write((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Write reg command error!"), edit);
            return 3;
        }

#ifdef CHECK
        rdri.setRegAddr(regAddr);
        rdri.calculateCrc();
        writeLog(rdri.getDataString(), edit);
        ret = c.Write((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Read reg command send error!"), edit);
            return 3;
        }


        readLength = rdrr.bufferSize();
        ret = c.Read((TCHAR *)rdrr.bufferSrc(), rdrr.bufferSize(), &readLength);
        if (ret != 0)
        {
            writeLog(std::string("Read reg command receive error!"), edit);
            return 3;
        }
        rdrr.format();
        if (rdrr.checkResponceHead())
        {
            writeLog(std::string("checkResponceHead error!"), edit);
        }
        if (rdrr.checkResponceCrc())
        {
            writeLog(std::string("checkResponceCrc error!"), edit);
        }
        if (rdrr.checkMagicNum1())
        {
            writeLog(std::string("checkMagicNum1 error!"), edit);
        }
        writeLog(rdrr.getDataString(), edit);
#endif
    }
#else

    Rwe tmpCase;
    for (size_t i = 0; i < getSize(); i++)
    {
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
        
        writeLog(wdri.getDataString(), edit);


        ret = c.Write((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Write reg command error!"), edit);
            return 3;
        }

#ifdef CHECK
        rdri.setRegAddr(regAddr);
        rdri.calculateCrc();
        writeLog(rdri.getDataString(), edit);
        ret = c.Write((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Read reg command send error!"), edit);
            return 3;
        }


        readLength = rdrr.bufferSize();
        ret = c.Read((TCHAR *)rdrr.bufferSrc(), rdrr.bufferSize(), &readLength);
        if (ret != 0)
        {
            writeLog(std::string("Read reg command receive error!"), edit);
            return 3;
        }
        rdrr.format();
        if (rdrr.checkResponceHead())
        {
            writeLog(std::string("checkResponceHead error!"), edit);
            //return 3;
        }
        if (rdrr.checkResponceCrc())
        {
            writeLog(std::string("checkResponceCrc error!"), edit);
           // return 3;
        }
        if (rdrr.checkMagicNum1())
        {
            writeLog(std::string("checkMagicNum1 error!"), edit);
            //return 3;
        }
        writeLog(rdrr.getDataString(), edit);
#endif
    }
#endif // UseFileInit

    return 0;
}

int writeDataFlow(CSerial &c, CEdit &edit)
{
    int ret = 0;
    readHexFile initHexFile(RegFilePath);
    CwriteDdrRegInput wdri;
    CreadDdrRegInput rdri;
    CreadDdrRegResponce rdrr;

    unsigned int regAddr = 0;
    unsigned int regData = 0;
    DWORD readLength = 0;

    wdri.setType(3);
    wdri.setUnicast();
    wdri.setLowFlagReg();
    wdri.setChipAddr(0);

    rdri.setType(6);
    rdri.setUnicast();
    rdri.setLowFlagReg();
    rdri.setChipAddr(0);
#ifdef UseFileInit
    std::array<unsigned int, 3> tmpCase;
    initHexFile.readInitData();
    for (size_t i = 0; i < initHexFile.initData.size(); i++)
    {
        tmpCase = initHexFile.initData[i];
        if (tmpCase[0])
        {
            regAddr = 0x0002000;
        }
        else
        {
            regAddr = 0x0000000;
        }

        regAddr += tmpCase[1];
        regData = tmpCase[2];

        wdri.setRegAddr(regAddr);
        wdri.setData(regData);
        wdri.calculateCrc();

        writeLog(wdri.getDataString(), edit);


        ret = c.Write((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Write reg command error!"), edit);
            return 3;
        }

#ifdef CHECK
        rdri.setRegAddr(regAddr);
        rdri.calculateCrc();
        writeLog(rdri.getDataString(), edit);
        ret = c.Write((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Read reg command send error!"), edit);
            return 3;
        }


        readLength = rdrr.bufferSize();
        ret = c.Read((TCHAR *)rdrr.bufferSrc(), rdrr.bufferSize(), &readLength);
        if (ret != 0)
        {
            writeLog(std::string("Read reg command receive error!"), edit);
            return 3;
        }
        rdrr.format();
        if (rdrr.checkResponceHead())
        {
            writeLog(std::string("checkResponceHead error!"), edit);
        }
        if (rdrr.checkResponceCrc())
        {
            writeLog(std::string("checkResponceCrc error!"), edit);
        }
        if (rdrr.checkMagicNum1())
        {
            writeLog(std::string("checkMagicNum1 error!"), edit);
        }
        writeLog(rdrr.getDataString(), edit);
#endif
    }
#else

    Rwe tmpCase;
    for (size_t i = 0; i < getSize(); i++)
    {
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

        writeLog(wdri.getDataString(), edit);


        ret = c.Write((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Write reg command error!"), edit);
            return 3;
        }

#ifdef CHECK
        rdri.setRegAddr(regAddr);
        rdri.calculateCrc();
        writeLog(rdri.getDataString(), edit);
        ret = c.Write((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());
        if (ret != 0)
        {
            writeLog(std::string("Read reg command send error!"), edit);
            return 3;
        }


        readLength = rdrr.bufferSize();
        ret = c.Read((TCHAR *)rdrr.bufferSrc(), rdrr.bufferSize(), &readLength);
        if (ret != 0)
        {
            writeLog(std::string("Read reg command receive error!"), edit);
            return 3;
        }
        rdrr.format();
        if (rdrr.checkResponceHead())
        {
            writeLog(std::string("checkResponceHead error!"), edit);
            //return 3;
        }
        if (rdrr.checkResponceCrc())
        {
            writeLog(std::string("checkResponceCrc error!"), edit);
            // return 3;
        }
        if (rdrr.checkMagicNum1())
        {
            writeLog(std::string("checkMagicNum1 error!"), edit);
            //return 3;
        }
        writeLog(rdrr.getDataString(), edit);
#endif
    }
#endif // UseFileInit

    return 0;
}

int writeOneReg(CSerial &c, unsigned int addr, unsigned int data, CEdit &edit)
{
    int ret = 0;
    CwriteDdrRegInput wdri;
    wdri.setType(3);
    wdri.setUnicast();
    wdri.setLowFlagReg();
    wdri.setChipAddr(0);

    wdri.setRegAddr(addr);
    wdri.setData(data);
    wdri.calculateCrc();
    writeLog(wdri.getDataString(), edit);

    c.Write((const TCHAR*)wdri.bufferSrc(), wdri.bufferSize());
    return 0;
}

int readOneReg(CSerial &c, unsigned int addr, unsigned int *addrData, CEdit &edit)
{
    int ret = 0;
    unsigned int regAddr = 0;
    unsigned int regData = 0;
    DWORD readLength = 0;
    CreadDdrRegInput rdri;
    CreadDdrRegResponce rdrr;

    regAddr = addr;

    rdri.setType(6);
    rdri.setUnicast();
    rdri.setLowFlagReg();
    rdri.setChipAddr(0);
    rdri.setRegAddr(regAddr);
    rdri.calculateCrc();
    writeLog(rdri.getDataString(), edit);
    c.Write((const TCHAR*)rdri.bufferSrc(), rdri.bufferSize());

    readLength = rdrr.bufferSize();
    c.Read((TCHAR *)rdrr.bufferSrc(), rdrr.bufferSize(), &readLength);

    rdrr.format();
    *addrData = rdrr.getRegData();
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
    writeLog(rdrr.getDataString(), edit);
    return 0;
}

int writeDdrData(CSerial &c, unsigned int ad, unsigned char *ddrData, unsigned int ddrDataLen, CEdit &edit)
{
    CwriteDdrDataInput wddi;

    int addrTest = 0x0000;

    if (ad)
    {
        addrTest = ad;
    }

    wddi.setType(3);
    wddi.setUnicast();
    wddi.clearLowFlagReg();
    wddi.setChipAddr(0);
    wddi.setDdrAddr(addrTest);
    wddi.setData(ddrData, ddrDataLen);
    wddi.calculateCrc();
    writeLog(wddi.getDataString(), edit);

    c.Write((const TCHAR*)wddi.bufferSrc(), wddi.bufferSize());

    return 0;
}

int readDdrData(CSerial &c, unsigned int ad, unsigned char *ddrData, unsigned int ddrDataLen, CEdit &edit)
{
    CreadDdrDataInput rddi;
    CreadDdrDataResponce rddr;

    unsigned int addrTest = 0x0000;
    DWORD readLength = 0;

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
    writeLog(rddi.getDataString(), edit);

    c.Write((const TCHAR*)rddi.bufferSrc(), rddi.bufferSize());
    std::cout << "read data:" << std::endl;
    readLength = rddr.bufferSize();
    c.Read((TCHAR *)rddr.bufferSrc(), rddr.bufferSize(), &readLength);
    rddr.format();
    if (rddr.checkResponceHead())
    {
        writeLog(std::string("checkResponceHead error!"), edit);
    }
    if (rddr.checkResponceCrc())
    {
        writeLog(std::string("checkResponceCrc error!"), edit);
    }
    if (rddr.checkMagicNum1())
    {
        writeLog(std::string("checkMagicNum1 error!"), edit);
    }
    writeLog(rddr.getDataString(), edit);

    return 0;
}


