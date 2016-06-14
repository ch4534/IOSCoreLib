#ifndef OLIDRIVER_H
#define OLIDRIVER_H

#include "Driver.h"
extern "C"{
    
class OLIDriver : public Driver
{
public:
    OLIDriver();
    virtual ~OLIDriver();  
    
public:
    virtual int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) override;

private:
    virtual byte** get24Rows(long row) override;
    int InnerRemixBmpInOLI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength);
    void twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
};

}

#endif