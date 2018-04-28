#pragma once
#include <bitset>


class CbmRegister32
{
public:
    CbmRegister32();
    ~CbmRegister32();

    int set(const unsigned int value);
    int set(const unsigned int start, const unsigned int end, const unsigned int value);
    int get(unsigned int *value);
    int get(const unsigned int start, const unsigned int end, unsigned int *value);

    int read();
    int write();

    void enableDebug(void);
    void disableDebug(void);

private:
    std::bitset<32> r;
    bool debugFlag;
};

