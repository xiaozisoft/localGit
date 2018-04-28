#pragma once

typedef struct regWriteExam {
    unsigned int baseAddr;
    unsigned int offsetAddr;
    unsigned int data;
}Rwe;

extern Rwe initDataFlow[];
unsigned int getSize(void);
void setWindowValue(unsigned char v, unsigned int pos);
void setTestValue(unsigned int v);

