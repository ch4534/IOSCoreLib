#include "stdinc.h"
#include "MPDriver.h"

MPDriver::MPDriver():Driver()
{
    mXDPI = 168;
    mYDPI = 144;
    mPickPointPerCol = 16;
    mESCM = 0x03;
}

MPDriver::~MPDriver()
{

}

int MPDriver::InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    mXDPI = xDPI;
    mYDPI = yDPI;
    
    return InnerRemixBmpInMP(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
}

int MPDriver::InnerRemixBmpInMP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength)
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
  
  setEscDPI();
  
 pPrintData[myxPos + 0] = 0x1b;
 pPrintData[myxPos + 1] = 0x40;
 
 myxPos += 2;
 
 int lYinPix = abs(ly) * 168.f / 254.f;
 int icounts = lYinPix / 255;
 
 if (ly > 0)
 {
   for (int i = 0; i < icounts; ++i)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x4a;
     pPrintData[myxPos + 3] = 0xff;
     myxPos += 4;
   }
   
   lYinPix &= 0xff;
   if (lYinPix > 0 || lYinPix < 0)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x4a;
     pPrintData[myxPos + 3] = lYinPix;
     myxPos += 4;
   }
 }
 else
 {
   for (int i = 0; i < icounts; ++i)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x6a;
     pPrintData[myxPos + 3] = 0xff;
     myxPos += 4;
   }
   
   lYinPix &= 0xff;
   if (lYinPix > 0 || lYinPix < 0)
   {
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x6a;
     pPrintData[myxPos + 3] = lYinPix;
     myxPos += 4;
   }
 }
 
 long height = bmpHeight;
 
 int skipLines = 0;
 byte** DataBlock = 0;
 long ht = 0;
 long lXinPix = lx * 144 / 254;
 
//  float skipBlankLineFactor = 1;
//  switch (mPickPointPerCol)
//  {
//      case 8:
//         skipBlankLineFactor = 2;
//         break;
//  }
 
 float skipBlankColsFactor = 1;
 switch (mXDPI)
 {
     case 84:
        skipBlankColsFactor = 2;
        break;
 }
 
 while (ht < height)
 {
   skipLines = 0;
   
   byte tempByte = (byte)(0x80 >> (ht & 0x07));
   while ((mpBlankInfo[ht >> 3] & tempByte)&& (ht < height))
   {
     ++ht;
     ++skipLines;
   }
   
   if (skipLines > 0)
   {
     int iSkipYpos = skipLines;
     
     iSkipYpos = (float)iSkipYpos / mYDPI * 144.f;
     int iSkipCounts = iSkipYpos / 255;
     for (int i = 0; i < iSkipCounts; ++i)
     {
       pPrintData[myxPos + 0] = 0x0d;
       pPrintData[myxPos + 1] = 0x1b;
       pPrintData[myxPos + 2] = 0x4a;
       pPrintData[myxPos + 3] = 0xff;
       myxPos += 4;
     }
     
     iSkipYpos &= 0xff;
     if (iSkipYpos != 0)
     {
       pPrintData[myxPos + 0] = 0x0d;
       pPrintData[myxPos + 1] = 0x1b;
       pPrintData[myxPos + 2] = 0x4a;
       pPrintData[myxPos + 3] = iSkipYpos;
       myxPos += 4;
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
     pPrintData[myxPos + 2] = (byte)(lXinPix % 256);
     pPrintData[myxPos + 3] = (byte)(lXinPix / 256);
     myxPos += 4;
   }
   
   if (mPickPointPerCol == 8)
   {
       DataBlock = get8Rows(ht);
       if (DataBlock == nullptr)
       {
           break;
       }
       ht += 8;
       
       eightPointPerCol(DataBlock, pPrintData, skipBlankColsFactor);
       
       for (long i = 0; i < mBmpWidth; ++i)
       {
            delete[] DataBlock[i];
       }
   
       delete[] DataBlock;
   }
   else if (mPickPointPerCol == 16)
   {
       DataBlock = get16Rows(ht);
       if (DataBlock == nullptr)
       {
           break;
       }
       ht += 16;
       
       sixteenPointPerCol(DataBlock, pPrintData, skipBlankColsFactor);
       
       for (long i = 0; i < mBmpWidth; ++i)
       {
            delete[] DataBlock[i];
       }
   
       delete[] DataBlock;
   }
 }
 
 pPrintData[myxPos + 0] = 0x0c;
 ++myxPos;
  
  return myxPos;
}

void MPDriver::setEscDPI()
{
    if (mXDPI == 84 && mYDPI == 72)
    {
        mESCM = 0x00;
        mPickPointPerCol = 8;
    }
    else if (mXDPI == 168 && mYDPI == 144)
    {
        mESCM = 0x03;
        mPickPointPerCol = 16;
    }
}

void MPDriver::eightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    
    while (wt < width)
    {
        while ((wt < width) && ((DataBlock[wt][0]) == 0x00))
        {
            ++wt;
        }
        
        iBlankCols = wt * skipRowBlankLineFactor;
        if (iBlankCols > 0)
        {
            OutputData[myxPos + 0] = 0x1b;
            OutputData[myxPos + 1] = 0x24;
            OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
            OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
            myxPos += 4;
        }

        if (wt >= width)
        {
            break;
        }
        
        while (wt < width && ((DataBlock[wt][0]) != 0x00))
        {
            ++wt;
            ++iDataCols;
        }
        
        OutputData[myxPos + 0] = 0x1b;
        OutputData[myxPos + 1] = 0x2a;
        OutputData[myxPos + 2] = mESCM;
        OutputData[myxPos + 3] = (byte)(iDataCols % 256);
        OutputData[myxPos + 4] = (byte)(iDataCols / 256);
        myxPos += 5;
        
        for (long m = 0; m < iDataCols; ++m)
        {
            OutputData[myxPos + 0] = DataBlock[wt - iDataCols + m][0];
            myxPos += 1;
        }
        iDataCols = 0;
    }
    
    int nSkipLines = 8.f / 72.f * 144.f;
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x4a;
    OutputData[myxPos + 3] = nSkipLines;
    myxPos += 4;
}

void MPDriver::sixteenPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    
    while (wt < width)
    {
        while ((wt < width) && ((DataBlock[wt][0] | DataBlock[wt][1]) == 0x00))
        {
            ++wt;
        }
        
        iBlankCols = wt * skipRowBlankLineFactor;
        if (iBlankCols > 0)
        {
            OutputData[myxPos + 0] = 0x1b;
            OutputData[myxPos + 1] = 0x24;
            OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
            OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
            myxPos += 4;
        }

        if (wt >= width)
        {
            break;
        }
        
        while (wt < width && ((DataBlock[wt][0] | DataBlock[wt][1]) != 0x00))
        {
            ++wt;
            ++iDataCols;
        }
        
        OutputData[myxPos + 0] = 0x1b;
        OutputData[myxPos + 1] = 0x2a;
        OutputData[myxPos + 2] = mESCM;
        OutputData[myxPos + 3] = (byte)(iDataCols * 2 % 256);
        OutputData[myxPos + 4] = (byte)(iDataCols * 2 / 256);
        myxPos += 5;
        
        for (long m = 0; m < iDataCols; ++m)
        {
            OutputData[myxPos + 0] = DataBlock[wt - iDataCols + m][0];
            OutputData[myxPos + 1] = DataBlock[wt - iDataCols + m][1];
            myxPos += 2;
        }
        iDataCols = 0;
    }
    
    int nSkipLines = 8.f / 144.f * 144.f;
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x4a;
    OutputData[myxPos + 3] = nSkipLines;
    myxPos += 4;
}

byte** MPDriver::get16Rows(long row)
{
    byte** m2ByteTable = nullptr;
    
    if (row < mBmpHeight)
    {
        m2ByteTable = new byte*[mBmpWidth];
        for (long i = 0; i < mBmpWidth; ++i)
        {
            m2ByteTable[i] = new byte[2];
            for (int j = 0; j < 2; ++j)
            {
                m2ByteTable[i][j] = 0x00;   
            }
        }
        
        long offset = row + 16;
        if (offset > mBmpHeight)
        {
            offset = mBmpHeight;
        }
        
        byte tempH = 0;
        while (row < offset)
        {
            byte tempByte = (byte)(0x80 >> (tempH & 0x07));
            for (long i = 0; i < mBmpWidth; ++i)
            {
                long curPos = row * mBmpWidth + i;
                byte curPosByte = (byte)(0x80 >> (curPos & 0x07));
                if ((mpBWData[curPos >> 3] & curPosByte) != 0)
                {
                    m2ByteTable[i][tempH >> 3] |= tempByte;
                }
            }
            
            ++row;
            ++tempH;
        }
    }
    
    return m2ByteTable;
}