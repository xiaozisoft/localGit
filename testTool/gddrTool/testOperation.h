#pragma once
#include "Serial.h"

int setAddrInit(CSerial &c, CEdit &edit);
int testOneReg(CSerial &c, CEdit &edit);
int initGddrDataFlow(CSerial &c, CEdit &edit);

int readOneReg(CSerial &c, unsigned int addr, unsigned int *addrData, CEdit &edit);
int writeOneReg(CSerial &c, unsigned int addr, unsigned int data, CEdit &edit);
int writeDdrData(CSerial &c, unsigned int ad, unsigned char *ddrData, unsigned int ddrDataLen, CEdit &edit);
int readDdrData(CSerial &c, unsigned int ad, unsigned char *ddrData, unsigned int ddrDataLen, CEdit &edit);


