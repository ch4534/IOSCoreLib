#ifndef OKIDRIVER_H
#define OKIDRIVER_H

#include "Driver.h"
extern "C"{
    
class OKIDriver : public Driver
{
public:
    OKIDriver();
    virtual ~OKIDriver();  
    
public:
    virtual int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) override;
    
private:
    int InnerRemixBmpInOKI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength);
    void twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
};

}
#endif