#pragma once

#include "Communication.h"
#include "CreadDdrRegInput.h"
#include "CreadDdrRegRespoce.h"

int testInit(Communication &c);
int testOneReg(Communication &c);
int testAllReg(Communication &c);
int initFlow(Communication &c);
int writeDdrData(Communication &c, unsigned int ad);
int readDdrData(Communication &c, unsigned int ad);

int readOneReg(Communication &c, unsigned int addr);
int writeOneReg(Communication &c, unsigned int addr, unsigned int data);


