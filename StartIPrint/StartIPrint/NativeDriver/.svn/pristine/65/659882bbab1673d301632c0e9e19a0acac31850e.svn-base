#ifndef MPDRIVER_H
#define MPDRIVER_H

#include "Driver.h"
extern "C"{
    
class MPDriver : public Driver
{
public:
    MPDriver();
    virtual ~MPDriver();  
    
private:
    int mPickPointPerCol;    
    
public:
    virtual int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) override;
    
private:
    void setEscDPI();
    byte** get16Rows(long row);
    int InnerRemixBmpInMP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength);
    void eightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
    void sixteenPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
};
    
}

#endif