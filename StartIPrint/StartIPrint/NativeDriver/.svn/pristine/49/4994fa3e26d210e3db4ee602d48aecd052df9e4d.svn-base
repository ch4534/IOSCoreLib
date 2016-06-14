#ifndef EPOSADRIVER_H
#define EPOSADRIVER_H

#include "Driver.h"
extern "C"{
    
class EPOSADriver : public Driver
{
public:
    EPOSADriver();
    virtual ~EPOSADriver();  
    
public:
    virtual int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) override;
    
private:
    int InnerRemixBmpInEPOS(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength);
    void twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
};

}
#endif