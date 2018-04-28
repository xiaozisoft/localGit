// testTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "Serial.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>
#include <array>
#include <iomanip>
#include "Ccrc.h"
#include "Communication.h"
#include "CreadDdrRegInput.h"
#include "CwriteDdrRegInput.h"
#include "CreadDdrRegRespoce.h"
#include "testReadWriteReg.h"
#include "testInitConf.h"

//#define SendTest

int ShowError(LONG lError, LPCTSTR lptszMessage)
{
    // Generate a message text
    TCHAR tszMessage[256];
    wsprintf(tszMessage, _T("%s\n(error code %d)"), lptszMessage, lError);

    // Display message-box and return with an error-code
    ::MessageBox(0, tszMessage, _T("Hello world"), MB_ICONSTOP | MB_OK);
    return 1;
}

int test1(void)
{
    CSerial serial1;

    LONG lastError = ERROR_SUCCESS;

    // Attempt to open the serial port (COM1)
    lastError = serial1.Open(_T("COM1"), 0, 0, false);
    if (lastError != ERROR_SUCCESS)
        return ::ShowError(serial1.GetLastError(), _T("Unable to open COM-port"));

    // Setup the serial port (9600,N81) using hardware handshaking
    lastError = serial1.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
    if (lastError != ERROR_SUCCESS)
        return ::ShowError(serial1.GetLastError(), _T("Unable to set COM-port setting"));

    // Setup handshaking
    lastError = serial1.SetupHandshaking(CSerial::EHandshakeOff);
    if (lastError != ERROR_SUCCESS)
        return ::ShowError(serial1.GetLastError(), _T("Unable to set COM-port handshaking"));

    // The serial port is now ready and we can send/receive data. If
    // the following call blocks, then the other side doesn't support
    // hardware handshaking.
    lastError = serial1.Write("Hello world ! \n\n");
    if (lastError != ERROR_SUCCESS)
        return ::ShowError(serial1.GetLastError(), _T("Unable to send data"));

    // Close the port again
    serial1.Close();
    return 0;
}

int test2(void)
{
    LONG lastError = ERROR_SUCCESS;

    Communication serialCom1("COM1");

    lastError = serialCom1.config(115200);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("configure com error!"));
    }

    std::array<uint8_t, 14> regInput;
    regInput[0] = 0x55;
    regInput[1] = 0xaa;
    regInput[2] = 0x3 << 4 | 0 | 0;
    regInput[3] = 0x00;
    regInput[4] = 0x00;
    regInput[5] = 0x00;
    regInput[6] = 0x20;
    regInput[7] = 0x00;
    regInput[8] = 0x00;
    regInput[9] = 0x00;
    regInput[10] = 0x00;
    regInput[11] = 0x00;

    uint16_t inputCrc = 0;

    inputCrc = CRC16(regInput.data(), (uint16_t)regInput.size() - sizeof(uint16_t));

    std::cout << std::hex << std::setw(4) << std::setfill('0') << inputCrc << std::endl;


    regInput[12] = (inputCrc & 0xff00) >> 8;
    regInput[13] = inputCrc & 0xff;

    for (auto a : regInput)
    {
        int i = a;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << i << " ";
    }
    std::cout << std::endl;

    serialCom1.writeData((TCHAR *)regInput.data(), regInput.size());

    return 0;
}

int test3(void)
{
    LONG lastError = ERROR_SUCCESS;

    Communication serialCom1("COM1");

    lastError = serialCom1.config(115200);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("configure com error!"));
    }

    TCHAR inactiveMsg[] = { 0x55, 0xaa, 0x2b, 0x07, 0x00, 0x00, 0x08 };
    TCHAR setAddrMsg[] = { 0x55, 0xaa, 0x20, 0x07, 0x00, 0x00, 0x11 };
    TCHAR configMsg[] = { 0x55, 0xaa, 0x21, 0x0b, 0x00, 0xc0, 0x9e, 0x64, 0x03, 0x8a, 0x0b};
    TCHAR getStatusMsg[] = { 0x55, 0xaa, 0x22, 0x07, 0x00, 0xc0, 0x0a };


    lastError = serialCom1.writeData(inactiveMsg, 7);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("inactiveMsg send error!"));
    }
    lastError = serialCom1.writeData(setAddrMsg, 7);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("setAddrMsg send error!"));
    }
    lastError = serialCom1.writeData(configMsg, 11);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("configMsg send error!"));
    }

    lastError = serialCom1.writeData(getStatusMsg, 7);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("getStatusMsg send error!"));
    }

    int getBufLength = 12;
    TCHAR getDataBuf[12] = { 0 };

    lastError = serialCom1.readData(getDataBuf, &getBufLength);
    if (lastError != ERROR_SUCCESS)
    {
        return ::ShowError(lastError, _T("getDataBuf return error!"));
    }

    for (int j = 0; j < 12; j++)
    {
        int i = getDataBuf[j];
        std::cout << std::hex << std::setw(2) << std::setfill('0') << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

int testReadReg(void)
{
    CreadDdrRegInput readRegInput;

    readRegInput.setType(6);
    readRegInput.setUnicast();
    readRegInput.setLowFlagReg();
    readRegInput.setChipAddr(0);
    readRegInput.setRegAddr(0x0000000 + 0x20);
    readRegInput.calculateCrc();
    readRegInput.printOut();
    return 0;
}

int testWriteReg(void)
{
    CwriteDdrRegInput writeRegInput;

    writeRegInput.setType(3);
    writeRegInput.setUnicast();
    writeRegInput.setLowFlagReg();
    writeRegInput.setChipAddr(0);
    writeRegInput.setRegAddr(0x0000000 + 0x20);
    writeRegInput.setData(0x34285692);
    writeRegInput.calculateCrc();
    writeRegInput.printOut();

    return 0;
}

int readRegResponceTest(void)
{
    unsigned char data[] = { 0xaa, 0x55, 0x18, 0x00, 0x5e, 0x44, 0x64, 0x61, 0xb4, 0xb3 };

    CreadDdrRegResponce readResponse;

    memcpy(readResponse.bufferSrc(), data, readResponse.bufferSize());

    readResponse.format();
    if (readResponse.checkResponceHead())
    {
        std::cout << "checkResponceHead error" << std::endl;
    }
    if (readResponse.checkResponceCrc())
    {
        std::cout << "checkResponceCrc error" << std::endl;
    }
    if (readResponse.checkMagicNum1())
    {
        std::cout << "checkMagicNum1 error" << std::endl;
    }
    readResponse.printOut();

    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "param error!" << std::endl;
    }

    //for (auto i = 0; i < argc; i++)
    //{
    //    std::string tmp(argv[i]);
    //    std::cout << tmp << " ";
    //}
    std::cout << std::endl;
    std::string comPort;
    
    Communication c("COM3");
    //c.config(115200);

    testInit(c);
    testOneReg(c);
    //readOneReg(c, 0xc0);
    //readOneReg(c, 0x08);
    //readOneReg(c, 0xc4);
    unsigned int pos = 0;
    while (1)
    {
        unsigned int addr1 = 0;
        unsigned int dataWrite = 0;
        initFlow(c);

        for (size_t i = 0; i <= 0xf; i++)
        {
#ifdef FIST_VALUE
            setWindowValue(1, pos);
            //std::cin >> comPort;
            std::cout << comPort << std::endl;
#endif // FIST_VALUE
#ifdef SendTest
            setTestValue(i);
#endif
            writeOneReg(c, addr1, dataWrite);
            readOneReg(c, addr1);
            writeDdrData(c, 0x00);
            readDdrData(c, 0x00);
        }
    }

    //readRegResponceTest();

    system("PAUSE");
    return 0;
}

