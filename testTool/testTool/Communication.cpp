#include "stdafx.h"
#include "Communication.h"
#include <string>

Communication::Communication(const TCHAR *addr)
{
    lastError = comSerial.Open(addr, 0, 0, false);
}

Communication::~Communication()
{
    lastError = comSerial.Close();
}

int Communication::config(int baudrate)
{
    int baudTable[] = { 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000, 0xffffff };

    for (auto i = 0; i < sizeof(baudTable); i++)
    {
        if (baudrate == baudTable[i])
        {
            break;
        }
        else if(baudTable[i] == 0xffffffff)
        {
            return ERROR_BAD_ARGUMENTS;
        }
    }

    CSerial::EBaudrate baud;
    baud = CSerial::EBaudrate(baudrate);

    //Setup(EBaudrate eBaudrate, EDataBits eDataBits, EParity eParity, EStopBits eStopBits)
    lastError = comSerial.Setup(baud, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);

    comSerial.Purge();
    lastError = comSerial.SetupReadTimeouts(CSerial::EReadTimeoutBlocking);

    return lastError;
}

int Communication::writeData(const TCHAR *data, int dataLength)
{
    lastError = comSerial.Write(data, dataLength);
    return lastError;
}

int Communication::readData(TCHAR *data, int* dataLength)
{
    DWORD dataGet = 0;
    lastError = comSerial.Read((void *)data, *dataLength, &dataGet);
    *dataLength = dataGet;
    return lastError;
}

int Communication::conversation(TCHAR *dataDes, int *desLength, const TCHAR *dataSrc, int srcLength)
{
    DWORD dataGet = 0;

    lastError = comSerial.Write(dataSrc, srcLength);
    if(lastError != ERROR_SUCCESS)
    {
        return lastError;
    }
    lastError = comSerial.Read(dataDes, *desLength, &dataGet);
    if (lastError != ERROR_SUCCESS)
    {
        return lastError;
    }

    return lastError;
}