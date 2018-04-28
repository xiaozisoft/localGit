#pragma once
#include <bitset>

class CbyteStream
{
public:
    CbyteStream();
    ~CbyteStream();

    int set(const unsigned char value);
    int set(const unsigned int pos, const unsigned char value);
    int set(const unsigned int start, const unsigned int end, const unsigned char value);
    int get(unsigned char *value);
    int get(const unsigned int pos, unsigned char *value);
    int get(const unsigned int start, const unsigned int end, unsigned char *value);
private:
    std::bitset<8> oneByte;

};

