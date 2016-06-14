#ifndef LQDRIVER_H
#define LQDRIVER_H

#include "Driver.h"
extern "C"{
    
/**
* @brief LQ仿真解析
*/    
class LQDriver : public Driver
{
public:
    LQDriver();
    virtual ~LQDriver();  
    
private:
    int mPickPointPerCol;
    
public:
    int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) override;
 
protected:  
    void setEscMByDPI();
    int InnerRemixBmpInLQ(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength);
    void eightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
    void twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
    void fortyeightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor);
    byte** get48Rows(long row);
};

}

#endif