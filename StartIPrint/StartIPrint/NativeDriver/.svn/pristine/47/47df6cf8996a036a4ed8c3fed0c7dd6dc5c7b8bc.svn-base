#include "stdinc.h"
#include "EPOSADriver.h"

EPOSADriver::EPOSADriver():Driver()
{

}

EPOSADriver::~EPOSADriver()
{

}

int EPOSADriver::InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    return InnerRemixBmpInEPOS(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
}

int EPOSADriver::InnerRemixBmpInEPOS(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength)
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
  
  // releasePointers(&mpGrayData);
  delete[] mpGrayData;
  mpGrayData = nullptr;
  
  myxPos = 0;
  
 pPrintData[myxPos + 0] = 0x1b;
 pPrintData[myxPos + 1] = 0x40;
 
 myxPos += 2;
 
 int lYinPix = abs(ly) * 300.f / 254.f;
 int icounts = lYinPix / 255;
 
 if (ly > 0)
 {
   for (int i = 0; i < icounts; ++i)
   {
     pPrintData[myxPos + 0] = 0x1b;
     pPrintData[myxPos + 1] = 0x4a;
     pPrintData[myxPos + 2] = 0xff;
     myxPos += 3;
   }
   
   lYinPix &= 0xff;
   if (lYinPix > 0 || lYinPix < 0)
   {
     pPrintData[myxPos + 0] = 0x1b;
     pPrintData[myxPos + 1] = 0x4a;
     pPrintData[myxPos + 2] = (byte)lYinPix;
     myxPos += 3;
   }
 }
 
 long height = bmpHeight;
 
 int skipLines = 0;
 byte** DataBlock = 0;
 long ht = 0;
 long lXinPix = lx * 300 / 254;
 
 float skipBlankLineFactor = 1;
 float skipBlankColFactor = 1;
 
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
     int iSkipYpos = skipLines * skipBlankLineFactor;
     int iSkipCounts = iSkipYpos / 255;
     for (int i = 0; i < iSkipCounts; ++i)
     {
       pPrintData[myxPos + 0] = 0x1b;
       pPrintData[myxPos + 1] = 0x4a;
       pPrintData[myxPos + 2] = 0xff;
       myxPos += 3;
     }
     
     iSkipYpos &= 0xff;
     if (iSkipYpos != 0)
     {
       pPrintData[myxPos + 0] = 0x1b;
       pPrintData[myxPos + 1] = 0x4a;
       pPrintData[myxPos + 2] = (byte)iSkipYpos;
       myxPos += 3;
     }
   }
   
   if (ht >= height)
   {
     break;
   }
   
   if (lXinPix > 0)
   {
     pPrintData[myxPos + 0] = 0x1b;
     pPrintData[myxPos + 1] = 0x24;
     pPrintData[myxPos + 2] = lXinPix % 256;
     pPrintData[myxPos + 3] = lXinPix / 256;
     myxPos += 4;
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

void EPOSADriver::twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    
    while ((wt < width) && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2]) == 0x00))
    {
        ++wt;
    }
    
    iBlankCols = (int)(wt * skipRowBlankLineFactor);
    
    if (iBlankCols > 0)
    {
        OutputData[myxPos + 0] = 0x1b;
        OutputData[myxPos + 1] = 0x24;
        OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
        OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
        myxPos += 4; 
    }
    
    iDataCols = width - wt;
    int lineBytes = (int)(iDataCols / 8) + (iDataCols % 8 != 0 ? 1 : 0);
    
    OutputData[myxPos + 0] = 0x1d;
    OutputData[myxPos + 1] = 0x76;
    OutputData[myxPos + 2] = 0x30;
    OutputData[myxPos + 3] = 0x00;
    OutputData[myxPos + 4] = (byte)(lineBytes % 256);
    OutputData[myxPos + 5] = (byte)(lineBytes / 256);
    myxPos += 6;
    
    byte tempH = 0;
    int irow = 0;
    while (irow < 24)
    {
        byte tempByte = (byte)(0x80 >> (tempH & 0x07));
        byte data = 0x00;
        int j = 0;
        for (long i = wt; i < width; ++i, ++j)
        {
            data |= (((byte)(DataBlock[i][tempH >> 3] & tempByte) << (tempH & 0x07)) >> j);
            
            if (j == 8)
            {
                OutputData[myxPos++] = data;
                j = 0;
                data = 0x00;
            }
        }
        
        if (j > 0)
        {
            OutputData[myxPos++] = data;
        }
        
        ++irow;
        ++tempH;
    }
}