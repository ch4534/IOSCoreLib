#include "stdinc.h"
#include "OKIDriver.h"

OKIDriver::OKIDriver():Driver()
{

}

OKIDriver::~OKIDriver()
{

}

int OKIDriver::InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    return InnerRemixBmpInOKI(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
}

int OKIDriver::InnerRemixBmpInOKI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength)
{
  mBmpWidth = bmpWidth;
  mBmpHeight = bmpHeight;
  
  if (!isGrayData(bmpWidth, bytePerLine))
  {
    //灰度化
    mpGrayData = ConvertToGray(pBmpData, bytePerLine, bmpWidth, bmpHeight);
  }
  else
  {
    mpGrayData = pBmpData;
  }
  
  //二值化
  mpBlankInfo = ConvertToBW(mpGrayData, bmpWidth, bmpHeight);
  
  delete[] mpGrayData;
  mpGrayData = nullptr;
  
  myxPos = 0;
  
 pPrintData[myxPos + 0] = 0x18;
 pPrintData[myxPos + 1] = 0x0d;
 
 pPrintData[myxPos + 2] = 0x1b;
 pPrintData[myxPos + 3] = 0x36;
 
 myxPos += 4;
 
 int lYinPix = fabs(ly) * 120.f / 254.f;
 int icounts = lYinPix / 255;
 
 if (ly > 0)
 {
   for (int i = 0; i < icounts; ++i)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x25;
     pPrintData[myxPos + 3] = 0x35;
     pPrintData[myxPos + 4] = 0xff;
     myxPos += 5;
   }
   
   lYinPix &= 0xff;
   if (lYinPix > 0 || lYinPix < 0)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x25;
     pPrintData[myxPos + 3] = 0x35;
     pPrintData[myxPos + 4] = lYinPix;
     myxPos += 5;
   }
 }
 
 long height = bmpHeight;
 
 int skipLines = 0;
 byte** DataBlock = 0;
 long ht = 0;
 long lXinPix = lx * 180 / 254;
 
 while (ht < height)
 {
   skipLines = 0;
   
   byte tempByte = (byte)(0x80 >> (ht & 0x07));
   while ((mpBlankInfo[ht >> 3] & tempByte) && (ht < height))
   {
     ++ht;
     ++skipLines;
   }
   
   if (skipLines > 0)
   {
     int iSkipYpos = skipLines;
     
     iSkipYpos = (float)iSkipYpos / 180.f * 120.f;
     int iSkipCounts = iSkipYpos / 255;
     for (int i = 0; i < iSkipCounts; ++i)
     {
       pPrintData[myxPos + 0] = 0x0d;
       pPrintData[myxPos + 1] = 0x1b;
       pPrintData[myxPos + 2] = 0x25;
        pPrintData[myxPos + 3] = 0x35;
        pPrintData[myxPos + 4] = 0xff;
        myxPos += 5;
     }
     
     iSkipYpos &= 0xff;
     if (iSkipYpos != 0)
     {
       pPrintData[myxPos + 0] = 0x0d;
       pPrintData[myxPos + 1] = 0x1b;
       pPrintData[myxPos + 2] = 0x25;
       pPrintData[myxPos + 3] = 0x35;
       pPrintData[myxPos + 4] = iSkipYpos;
       myxPos += 5;
     }
   }
   
   if (ht >= height)
   {
     break;
   }
   
   if (lXinPix > 0)
   {
     pPrintData[myxPos + 0] = 0x1b;
     pPrintData[myxPos + 1] = 0x25;
     pPrintData[myxPos + 2] = 0x36;
     pPrintData[myxPos + 3] = lXinPix % 256;
     pPrintData[myxPos + 4] = lXinPix / 256;
     myxPos += 5;
   }
   
   DataBlock = get24Rows(ht);
   
   if (DataBlock == nullptr)
   {
       break;
   }
   
   ht += 24;
   
   twentyfourPointPerCol(DataBlock, pPrintData, 1);
   
   for (long i = 0; i < mBmpWidth; ++i)
   {
       delete[] DataBlock[i];
   }
   
   delete[] DataBlock;
 }
 
 pPrintData[myxPos + 0] = 0x0c;
 ++myxPos;
  
  return myxPos;
}

void OKIDriver::twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    
    while (wt < width)
    {
        while ((wt < width) && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2]) == 0x00))
        {
            ++wt;
            ++iBlankCols;
        }
        
        iBlankCols = iBlankCols * skipRowBlankLineFactor;
        if (iBlankCols > 0)
        {
            OutputData[myxPos + 0] = 0x1b;
            OutputData[myxPos + 1] = 0x25;
            OutputData[myxPos + 2] = 0x33;
            OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
            OutputData[myxPos + 4] = (byte)(iBlankCols % 256);
            myxPos += 5;
        }
        iBlankCols = 0;
        if (wt >= width)
        {
            break;
        }
        
        while (wt < width && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2]) != 0x00))
        {
            ++wt;
            ++iDataCols;
        }
        
        OutputData[myxPos + 0] = 0x1b;
        OutputData[myxPos + 1] = 0x25;
        OutputData[myxPos + 2] = 0x31;
        OutputData[myxPos + 3] = (byte)(iDataCols / 256);
        OutputData[myxPos + 4] = (byte)(iDataCols % 256);
        myxPos += 5;
        
        for (long m = 0; m < iDataCols; ++m)
        {
            OutputData[myxPos + 0] = DataBlock[wt - iDataCols + m][0];
            OutputData[myxPos + 1] = DataBlock[wt - iDataCols + m][1];
            OutputData[myxPos + 2] = DataBlock[wt - iDataCols + m][2];
            myxPos += 3;
        }
        iDataCols = 0;
    }
    
    int nSkipLines = (24.f / 180.f * 120.f);
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x25;
    OutputData[myxPos + 3] = 0x35;
    OutputData[myxPos + 4] = nSkipLines;
    myxPos += 5;
}