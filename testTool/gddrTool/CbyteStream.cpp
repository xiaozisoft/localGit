#include "stdafx.h"
#include "CbyteStream.h"


CbyteStream::CbyteStream()
{
    oneByte.reset();
}


CbyteStream::~CbyteStream()
{
}

int CbyteStream::set(const unsigned char value)
{
    unsigned char tmpVal = value;
    for (size_t i = 0; i < oneByte.size(); i++)
    {
        oneByte[i] = tmpVal & 0x1;
        tmpVal >>= 1;
    }
    return 0;
}

int CbyteStream::set(const unsigned int pos, const unsigned char value)
{
    if (pos >= 8)
    {
        return 1;
    }

    unsigned char tmpVal = value;

    oneByte[pos] = tmpVal & 0x1;

    return 0;
}

int CbyteStream::set(const unsigned int start, const unsigned int end, const unsigned char value)
{
    if (start >= 8 || end < 0 || start > end)
    {
        return 1;
    }

    unsigned char tmpVal = value;

    for (unsigned int i = start; i <= end; i++)
    {
        oneByte[i] = tmpVal & 0x1;
        tmpVal >>= 1;
    }

    return 0;
}

int CbyteStream::get(unsigned char *value)
{
    unsigned char tmpValue = 0;

    tmpValue = oneByte.to_ulong() & 0xff;
    //for (int i = 7; i >= 0; i--)
    //{
    //    tmpValue |= (oneByte[i] ? 1 : 0);
    //    tmpValue <<= 1;
    //}

    *value = tmpValue;
    return 0;
}

int CbyteStream::get(const unsigned int pos, unsigned char *value)
{
    if (pos >= 8)
    {
        return 1;
    }

    unsigned char tmpValue = 0;

    tmpValue |= (oneByte[pos] ? 1 : 0);

    *value = tmpValue;
    return 0;
}


int CbyteStream::get(const unsigned int start, const unsigned int end, unsigned char *value)
{
    if (start >= 8 || end < 0 || start > end)
    {
        return 1;
    }

    unsigned char tmpValue = 0;

    for (unsigned int i = end; i >= start; i--)
    {
        tmpValue |= (oneByte[i] ? 1 : 0);
        tmpValue <<= 1;
    }

    *value = tmpValue;
    return 0;
}
