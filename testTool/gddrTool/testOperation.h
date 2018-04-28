#pragma once
#include "Serial.h"

int setAddrInit(CSerial &c);
int testOneReg(CSerial &c);
int readOneReg(CSerial &c, unsigned int addr);
int writeOneReg(CSerial &c, unsigned int addr, unsigned int data);
int writeDdrData(CSerial &c, unsigned int ad);
int readDdrData(CSerial &c, unsigned int ad);


