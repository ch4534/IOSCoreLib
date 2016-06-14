#include "stdinc.h"
#include "LQDriver.h"

LQDriver::LQDriver():Driver()
{
    mXDPI = 180;
    mYDPI = 180;
    mESCM = 0x27;
    mPickPointPerCol = 24;
}

LQDriver::~LQDriver()
{

}

int LQDriver::InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    mXDPI = xDPI;
    mYDPI = yDPI;
    
    return this->InnerRemixBmpInLQ(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
}


int LQDriver::InnerRemixBmpInLQ(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength)
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
  
//   releasePointers(&mpGrayData);
  delete[] mpGrayData;
  mpGrayData = nullptr;
  
  myxPos = 0;
  
  this->setEscMByDPI();
  
 pPrintData[myxPos + 0] = 0x1b;
 pPrintData[myxPos + 1] = 0x40;
 
 pPrintData[myxPos + 2] = 0x1b;
 pPrintData[myxPos + 3] = 0x32;
 
 pPrintData[myxPos + 4] = 0x1b;
 pPrintData[myxPos + 5] = 0x43;
 
 int pageHeight = 297;
 byte pageRow = (byte)(pageHeight / 25.4 * 6);
 pPrintData[myxPos + 6] = pageRow;
 myxPos += 7;
 
 int lYinPix = abs(ly) * 180.f / 254.f;
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
 long lXinPix = lx * 60 / 254;
 
 float skipBlankLineFactor = 1.f;//纵方向走纸180分辨率，当前选择分辨率180
 //对于实达打印机来说，360 360分辨率是按360 180来进行计算
 switch (mPickPointPerCol)
 {
     case 8:
        skipBlankLineFactor = 3;
        break;
        
     case 48:
        skipBlankLineFactor = 1.f;
        break;
 }
 
 float skipBlankColFactor = 1.f;
 switch (mXDPI)
 {
     case 60:
        skipBlankColFactor = 3.f;
        break;
        
     case 120:
        skipBlankColFactor = 1.5f;
        break;
        
     case 240:
        skipBlankColFactor = 0.75f;
        break;
        
     case 80:
        skipBlankColFactor = 2.25f;
        break;
     
     case 90:
        skipBlankColFactor = 2.f;
        break;
     
     case 360:
        skipBlankColFactor = 0.5f;
        break;
        
     case 180:
     default:
        skipBlankColFactor = 1.f;
        break;
 }
 
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
     
     iSkipYpos = (float)iSkipYpos * skipBlankLineFactor;
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
     pPrintData[myxPos + 2] = lXinPix % 256;
     pPrintData[myxPos + 3] = lXinPix / 256;
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
       
       eightPointPerCol(DataBlock, pPrintData, skipBlankColFactor);
       
       for (long i = 0; i < mBmpWidth; ++i)
       {
           delete[] DataBlock[i];
       }
       
       delete[] DataBlock;
   }
   else if (mPickPointPerCol == 24)
   {
        DataBlock = get24Rows(ht);
   
        if (DataBlock == nullptr)
        {
            break;
        }
        
        ht += 24;
        
        twentyfourPointPerCol(DataBlock, pPrintData, skipBlankColFactor);
        
        for (long i = 0; i < mBmpWidth; ++i)
        {
            delete[] DataBlock[i];
        }
        
        delete[] DataBlock;
   }
   else if (mPickPointPerCol == 48)
   {
        DataBlock = get24Rows(ht);
   
        if (DataBlock == nullptr)
        {
            break;
        }
        
        ht += 24;
        
        fortyeightPointPerCol(DataBlock, pPrintData, skipBlankColFactor);
        
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

void LQDriver::eightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    
    while (wt < width)
    {
        while (wt < width && DataBlock[wt] == 0x00)
        {
            ++wt;
            ++iBlankCols;
        }
        
        iBlankCols = iBlankCols * skipRowBlankLineFactor;
        /** 设置水平相对打印位置 */
        if (iBlankCols > 0)
        {
            OutputData[myxPos + 0] = 0x1b;
            OutputData[myxPos + 1] = 0x5c;
            OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
            OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
            myxPos += 4;
        }
        
        iBlankCols = 0;
        if (wt >= width)
        {
            break;
        }
        
        while (wt < width && (DataBlock[wt][0] != 0x00))
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
    
    int SkipLines = 8 * 3;
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x4a;
    OutputData[myxPos + 3] = (byte)SkipLines;
    myxPos += 4;
}

void LQDriver::twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
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
            OutputData[myxPos + 1] = 0x5c;
            OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
            OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
            myxPos += 4;
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
        OutputData[myxPos + 1] = 0x2a;
        OutputData[myxPos + 2] = mESCM;
        OutputData[myxPos + 3] = (byte)(iDataCols % 256);
        OutputData[myxPos + 4] = (byte)(iDataCols / 256);
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
    
    int nSkipLines = (24.f / 180.f * 180.f);
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x4a;
    OutputData[myxPos + 3] = nSkipLines;
    myxPos += 4;
}

void LQDriver::fortyeightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_DEBUG, "NativeLQDriver", "fortyeightPointPerCol enter, xDPI = %d, yDPI = %d", mXDPI, mYDPI);
    __android_log_print(ANDROID_LOG_DEBUG, "NativeLQDriver", "skipRowBlankLineFactor = %f", skipRowBlankLineFactor);
    __android_log_print(ANDROID_LOG_DEBUG, "NativeLQDriver", "mESCM = %d", mESCM);
#endif
    for (int n = 0; n < 2; ++n)
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
            /** 设置水平相对打印位置 假定相对水平是180分辨率 */
            if (iBlankCols > 0)
            {
                OutputData[myxPos + 0] = 0x1b;
                OutputData[myxPos + 1] = 0x5c;
                OutputData[myxPos + 2] = (byte)(iBlankCols % 256);
                OutputData[myxPos + 3] = (byte)(iBlankCols / 256);
                myxPos += 4;
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
            OutputData[myxPos + 1] = 0x2a;
            OutputData[myxPos + 2] = mESCM;
            OutputData[myxPos + 3] = (byte)(iDataCols % 256);
            OutputData[myxPos + 4] = (byte)(iDataCols / 256);
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
        
        int nSkipLines = (1.f / 180.f * 180.f);
        OutputData[myxPos + 0] = 0x0d;
        OutputData[myxPos + 1] = 0x1b;
        OutputData[myxPos + 2] = 0x4a;
        OutputData[myxPos + 3] = nSkipLines;
        myxPos += 4;
    }
    
    int nSkipLines = (23.f / 180.f * 180.f);
    OutputData[myxPos + 0] = 0x0d;
    OutputData[myxPos + 1] = 0x1b;
    OutputData[myxPos + 2] = 0x4a;
    OutputData[myxPos + 3] = nSkipLines;
    myxPos += 4;
}

// void LQDriver::fortyeightPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
// {
//     long iDataCols = 0;
//     long iBlankCols = 0;
//     long wt = 0;
//     long width = mBmpWidth;
    
//     while (wt < width)
//     {
//         while ((wt < width) && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2] | DataBlock[wt][3] | DataBlock[wt][4] | DataBlock[wt][5]) == 0x00))
//         {
//             ++wt;
//             ++iBlankCols;
//         }
        
//         iBlankCols = iBlankCols * skipRowBlankLineFactor;
//         /** 设置水平相对打印位置 假定相对水平是180分辨率 */
//         if (iBlankCols > 0)
//         {
//             OutputData[myxPos + 0] = 0x1b;
//             OutputData[myxPos + 1] = 0x5c;
//             OutputData[myxPos + 2] = (byte)(iBlankCols / 256);
//             OutputData[myxPos + 3] = (byte)(iBlankCols % 256);
//             myxPos += 4;
//         }
//         iBlankCols = 0;
//         if (wt >= width)
//         {
//             break;
//         }
        
//         while (wt < width && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2] | DataBlock[wt][3] | DataBlock[wt][4] | DataBlock[wt][5]) != 0x00))
//         {
//             ++wt;
//             ++iDataCols;
//         }
        
//         OutputData[myxPos + 0] = 0x1b;
//         OutputData[myxPos + 1] = 0x2a;
//         OutputData[myxPos + 2] = mESCM;
//         OutputData[myxPos + 3] = (byte)(iDataCols % 256);
//         OutputData[myxPos + 4] = (byte)(iDataCols / 256);
//         myxPos += 5;
        
//         for (long m = 0; m < iDataCols; ++m)
//         {
//             OutputData[myxPos + 0] = DataBlock[wt - iDataCols + m][0];
//             OutputData[myxPos + 1] = DataBlock[wt - iDataCols + m][1];
//             OutputData[myxPos + 2] = DataBlock[wt - iDataCols + m][2];
//             OutputData[myxPos + 3] = DataBlock[wt - iDataCols + m][0];
//             OutputData[myxPos + 4] = DataBlock[wt - iDataCols + m][1];
//             OutputData[myxPos + 5] = DataBlock[wt - iDataCols + m][2];
//             myxPos += 6;
//         }
//         iDataCols = 0;
//     }
    
//     int nSkipLines = (48.f / 360.f * 180.f);
//     OutputData[myxPos + 0] = 0x0d;
//     OutputData[myxPos + 1] = 0x1b;
//     OutputData[myxPos + 2] = 0x4a;
//     OutputData[myxPos + 3] = nSkipLines;
//     myxPos += 4;
// }

byte** LQDriver::get48Rows(long row)
{
    byte** m6ByteTable = nullptr;
    
    if (row < mBmpHeight)
    {
        m6ByteTable = new byte*[mBmpWidth];
        
        for (long i = 0; i < mBmpWidth; ++i)
        {
            m6ByteTable[i] = new byte[6];
            for (int j = 0; j < 6; ++j)
            {
                m6ByteTable[i][j] = 0x00;
            }
        }
        
        long offset = row + 48;
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
                long curPos = mBmpWidth * row + i;
                byte curPosByte = (byte)(0x80 >> (curPos & 0x07));
                if ((mpBWData[curPos >> 3] & curPosByte) != 0)
                {
                    m6ByteTable[i][tempH >> 3] |= tempByte;
                }
            }
            
            ++row;
            ++tempH;
        }
    }
    
    return m6ByteTable;
}

void LQDriver::setEscMByDPI()
{
    if (mXDPI == 60 && mYDPI == 60){
            mESCM = 0x00;
            mPickPointPerCol = 8;
        }else if (mXDPI == 120 && mYDPI == 60){
            mESCM = 0x01;
            mPickPointPerCol = 8;
        }else if (mXDPI == 240 && mYDPI == 60){
            mESCM = 0x03;
            mPickPointPerCol = 8;
        }else if (mXDPI == 80 && mYDPI == 60){
            mESCM = 0x04;
            mPickPointPerCol = 8;
        }else if (mXDPI == 90 && mYDPI == 60){
            mESCM = 0x06;
            mPickPointPerCol = 8;
        }else if (mXDPI == 60 && mYDPI == 180){
            mESCM = 0x20;
            mPickPointPerCol = 24;
        }else if (mXDPI == 120 && mYDPI == 180){
            mESCM = 0x21;
            mPickPointPerCol = 24;
        }else if (mXDPI == 90 && mYDPI == 180){
            mESCM = 0x26;
            mPickPointPerCol = 24;
        }else if (mXDPI == 180 && mYDPI == 180){
            mESCM = 0x27;
            mPickPointPerCol = 24;
        }else if (mXDPI == 360 && mYDPI == 180){
            mESCM = 0x28;
            mPickPointPerCol = 24;
        }else if (mXDPI == 180 && mYDPI == 360){
            mESCM = 0x47;
            mPickPointPerCol = 48;
        }else if (mXDPI == 360 && mYDPI == 360){
            // mESCM = 0x48;
            mESCM = 0x28;
            mPickPointPerCol = 48;
        }
}