#pragma once
#include "stdafx.h"
#include <Windows.h>
#include "Serial.h"

#define CommunicationOk                 0x0
#define CommunicationConfigErr          0x01
#define CommunicationWriteErr           0x02
#define CommunicationReadErr            0x03
#define CommunicationConversationErr    0x04

class Communication
{
public:
    Communication(const TCHAR *addr);
    ~Communication();

    int config(int baudrate);
    int writeData(const TCHAR *data, int dataLength);
    int readData(TCHAR *data, int* dataLength);
    int conversation(TCHAR *dataDes, int *desLength, const TCHAR *dataSrc, int srcLength);

private:
    CSerial comSerial;
    LONG lastError;
};



