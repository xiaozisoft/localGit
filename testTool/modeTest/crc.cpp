#include "stdafx.h"
#include <cstring>

unsigned char CRC5(unsigned char *ptr, unsigned char len)
{
    unsigned char i, j, k;
    unsigned char crc = 0x1f;

    unsigned char crcin[5] = { 1, 1, 1, 1, 1 };
    unsigned char crcout[5] = { 1, 1, 1, 1, 1 };
    unsigned char din = 0;

    j = 0x80;
    k = 0;
    for (i = 0; i < len; i++)
    {
        if (*ptr & j)
        {
            din = 1;
        }
        else
        {
            din = 0;
        }
        crcout[0] = crcin[4] ^ din;
        crcout[1] = crcin[0];
        crcout[2] = crcin[1] ^ crcin[4] ^ din;
        crcout[3] = crcin[2];
        crcout[4] = crcin[3];

        j = j >> 1;
        k++;
        if (k == 8)
        {
            j = 0x80;
            k = 0;
            ptr++;
        }
        memcpy(crcin, crcout, 5);
    }
    crc = 0;
    if (crcin[4])
    {
        crc |= 0x10;
    }
    if (crcin[3])
    {
        crc |= 0x08;
    }
    if (crcin[2])
    {
        crc |= 0x04;
    }
    if (crcin[1])
    {
        crc |= 0x02;
    }
    if (crcin[0])
    {
        crc |= 0x01;
    }
    return crc;
}

/******************************************************************************
* Name:    CRC-5/USB           x5+x2+1
* Poly:    0x05
* Init:    0x1F
* Refin:   True
* Refout:  True
* Xorout:  0x1F
* Note:
*****************************************************************************/
unsigned char crc5usb(unsigned char *data, unsigned int length)
{
    unsigned char i;
    unsigned char crc = 0x1F;     // Initial value  

    while (length--)
    {
        crc ^= (*data);     // crc ^= *data; data++;  
        data++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0x14;// 0x14 = (reverse 0x05)>>(8-5)  
            else
                crc = (crc >> 1);
        }
    }
    return (crc ^ 0x1F);
}
