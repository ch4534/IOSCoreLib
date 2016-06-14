#include "stdinc.h"
#include "OLIDriver.h"

OLIDriver::OLIDriver():Driver()
{
}

OLIDriver::~OLIDriver()
{
}

int OLIDriver::InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    return this->InnerRemixBmpInOLI(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
}

int OLIDriver::InnerRemixBmpInOLI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength)
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
 
  int lYinPix = abs(ly) * 240.f / 254.f;
  if (lYinPix < 70)
  {
      lYinPix = 70;
  }
  
  pPrintData[myxPos + 0] = 0x0d;
  pPrintData[myxPos + 1] = 0x1b;
  pPrintData[myxPos + 2] = 0x2f;
  pPrintData[myxPos + 3] = 0x31;
  pPrintData[myxPos + 4] = (byte)(lYinPix / 1000);
  pPrintData[myxPos + 5] = (byte)(lYinPix / 100 % 10);
  pPrintData[myxPos + 6] = (byte)(lYinPix / 10 % 10);
  pPrintData[myxPos + 7] = (byte)(lYinPix % 10);
  myxPos += 8;
 
 long height = bmpHeight;
 
 int skipLines = 0;
 byte** DataBlock = 0;
 long ht = 0;
 long lXinPix = lx * 120 / 254;
 
 bool bSetImageModel = false;
 
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
     
     iSkipYpos = (float)iSkipYpos / 180.f * 240.f;
     lYinPix += iSkipYpos;
     
     pPrintData[myxPos + 0] = 0x0d;
     pPrintData[myxPos + 1] = 0x1b;
     pPrintData[myxPos + 2] = 0x2f;
     pPrintData[myxPos + 3] = 0x31;
     pPrintData[myxPos + 4] = (byte)(lYinPix / 1000);
     pPrintData[myxPos + 5] = (byte)(lYinPix / 100 % 10);
     pPrintData[myxPos + 6] = (byte)(lYinPix / 10 % 10);
     pPrintData[myxPos + 7] = (byte)(lYinPix % 10);
     myxPos += 8;
   }
   
   if (ht >= height)
   {
     break;
   }
   
   if (lXinPix > 0)
   {
     pPrintData[myxPos + 0] = 0x1b;
     pPrintData[myxPos + 1] = 0x7c;
     pPrintData[myxPos + 2] = 0x41;
     pPrintData[myxPos + 3] = (byte)(lXinPix / 100);
     pPrintData[myxPos + 4] = (byte)(lXinPix / 10 % 10);
     pPrintData[myxPos + 5] = (byte)(lXinPix % 10);
     myxPos += 6;
   }
   
   if (!bSetImageModel)
   {
       pPrintData[myxPos + 0] = 0x1b;
       pPrintData[myxPos + 1] = 0x21;
       pPrintData[myxPos + 2] = 0x47;
       pPrintData[myxPos + 3] = 0x31;
       myxPos += 4;
       bSetImageModel = true;
   }
   
   DataBlock = get24Rows(ht);
   
   if (DataBlock == nullptr)
   {
       break;
   }
   
   ht += 24;
   
   twentyfourPointPerCol(DataBlock, pPrintData, 1);
   
   // 一个数据带（3字节高）组织完毕，发送取消位图模式命令 + 纵向走纸命令
   pPrintData[myxPos + 0] = 0x1b;
   pPrintData[myxPos + 1] = 0x32;
   myxPos += 2;
   
   lYinPix += 32;
   pPrintData[myxPos + 0] = 0x0d;
   pPrintData[myxPos + 1] = 0x1b;
   pPrintData[myxPos + 2] = 0x2f;
   pPrintData[myxPos + 3] = 0x31;
   pPrintData[myxPos + 4] = (byte)(lYinPix / 1000);
   pPrintData[myxPos + 5] = (byte)(lYinPix / 100 % 10);
   pPrintData[myxPos + 6] = (byte)(lYinPix / 10 % 10);
   pPrintData[myxPos + 7] = (byte)(lYinPix % 10);
   myxPos += 8;
   
   for (long i = 0; i < mBmpWidth; ++i)
   {
       delete[] DataBlock[i];
   }
   
   delete[] DataBlock;
 }
 
 pPrintData[myxPos + 0] = 0x1b;
 pPrintData[myxPos + 1] = 0x7c;
 pPrintData[myxPos + 2] = 0x41;
 pPrintData[myxPos + 3] = 0x30;
 pPrintData[myxPos + 4] = 0x30;
 pPrintData[myxPos + 5] = 0x30;
 myxPos += 6;
 
 /** 加上0C命令进行换页命令 */
 pPrintData[myxPos + 0] = 0x0c;
 ++myxPos;
  
  return myxPos;
}

void OLIDriver::twentyfourPointPerCol(byte** DataBlock, byte* OutputData, float skipRowBlankLineFactor)
{
    OutputData[myxPos + 0] = 0x1b;
    OutputData[myxPos + 1] = 0x31;
    OutputData[myxPos + 2] = 0x41;
    OutputData[myxPos + 3] = 0x30;
    OutputData[myxPos + 4] = 0x30;
    OutputData[myxPos + 5] = 0x30;
    myxPos += 6;
    
    long iDataCols = 0;
    long iBlankCols = 0;
    long wt = 0;
    long width = mBmpWidth;
    bool bBlankBlock = true;			// 标识当前为空白字块
    
    for (int x = 0; x < width; x++)
    { // 4
        for (int y=0; y<3; y++)
        {// 5
            if (DataBlock[x][y]!=0x00)			// 当前字节非零,开始累计后续非零字节
            { // 6
                if(iBlankCols>1)				// 判断当前有没有横向空白量可以跳过 注，要空白量要大于5个字节，否则没必要发送横向定位指令
                { // 7
                  // 横向定位命令 1b 58 n n n 	相对水平位移	单位1/180
                    OutputData[myxPos + 0] = 0x1b;
                    OutputData[myxPos + 1] = 0x58;
                    OutputData[myxPos + 2] = (byte)(iBlankCols/100);
                    OutputData[myxPos + 3] = (byte)((iBlankCols/10)%10);
                    OutputData[myxPos + 4] = (byte)(iBlankCols%10);
                    myxPos += 5;

                    iBlankCols = 0;
                 }
                 else if(iBlankCols==1)   //  只有一列空白，也归为要打印数据
                 {
                     iDataCols++;
                     iBlankCols = 0;			//   空白量清零
                 }

                 iDataCols++;
                 bBlankBlock = false;
                 break;						// 纵向三个字节中只要有一个字节内容不为零，即要保留，并跳出本次y循环
             } //6 //
             else							// 当前字节为零
             { //6
                 bBlankBlock = true;
             } // 6 //
         } // 5//

         if (bBlankBlock)   //  每次Y轴循环判断完，如果三个字节都为零，则记录当前空白位置
         { // 5
                            // 判断当前有没有可打印数据要组织
            if (iDataCols > 0)
            { //6

                // 获取位图点阵数据，注意如果刚好有1b，要发送2次。否则会被当做指令而丢弃！！！
                for (int m = 0; m < iDataCols; m++)
                { //7
                    for(int n = 0; n < 3; n++)
                    { //8
                        OutputData[myxPos] = DataBlock[x-iDataCols+m][n];
                        myxPos++;

                        if (DataBlock[x-iDataCols+m][n] == 0x1b)
                        {
                            OutputData[myxPos] = 0x1b;
                            myxPos++;
                        }
                     } //8 //
                 } //7//
                                // 数据清零，之前的空白量位置清零
                 iDataCols = 0;
                 iBlankCols = 0;
             } // 6 //
             iBlankCols++;
          } //5//
      } // 4//
      // 整行校验结束，如果还有可打印数据未输出，说明数据块结尾不为空白
      if (iDataCols>0)
      { // 4
        // 获取位图点阵数据
        for (int m = 0; m < iDataCols; m++)
        { //5
            for(int n = 0; n < 3; n++)
            { //6
                OutputData[myxPos] = DataBlock[width - iDataCols+m][n];
                myxPos++;

                if (DataBlock[width-iDataCols+m][n] == 0x1b)
                {
                    OutputData[myxPos] = 0x1b;
                    myxPos++;
                }
             } //6//
         } //5//
        }//4//
    
    // while (wt < width)
    // {
    //     while ((wt < width) && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2]) == 0x00))
    //     {
    //         ++wt;
    //         ++iBlankCols;
    //     }
        
    //     iBlankCols = iBlankCols * skipRowBlankLineFactor;
    //     if (iBlankCols > 1)
    //     {
    //         OutputData[myxPos + 0] = 0x1b;
    //         OutputData[myxPos + 1] = 0x58;
    //         OutputData[myxPos + 3] = (byte)(iBlankCols / 100);
    //         OutputData[myxPos + 3] = (byte)(iBlankCols / 10 % 10);
    //         OutputData[myxPos + 4] = (byte)(iBlankCols % 10);
    //         myxPos += 5;
    //     }
    //     else if (iBlankCols == 1)
    //     {
    //         ++iDataCols;
    //     }
        
    //     iBlankCols = 0;
    //     if (wt >= width)
    //     {
    //         break;
    //     }
        
    //     while (wt < width && ((DataBlock[wt][0] | DataBlock[wt][1] | DataBlock[wt][2]) != 0x00))
    //     {
    //         ++wt;
    //         ++iDataCols;
    //     }
        
    //     for (long m = 0; m < iDataCols; ++m)
    //     {
    //         for (int n = 0; n < 3; ++n)
    //         {
    //             OutputData[myxPos] = DataBlock[wt - iDataCols + m][n];
    //             ++myxPos;
    //             if (DataBlock[wt - iDataCols + m][n] == 0x1b)
    //             {
    //                 OutputData[myxPos] = 0x1b;
    //                 ++myxPos;
    //             }
    //         }
    //     }

    //     iDataCols = 0;
    // }
}

byte** OLIDriver::get24Rows(long row)
{
  byte** m3ByteTable = nullptr;
  
  if (row < mBmpHeight)
  {
      m3ByteTable = new byte*[mBmpWidth];
      for (long i = 0; i < mBmpWidth; ++i)
      {
          m3ByteTable[i] = new byte[3];
          for (int j = 0; j < 3; ++j)
          {
              m3ByteTable[i][j] = 0x00;
          }
      }
      
      long offset = row + 24;
      if (offset > mBmpHeight)
      {
          offset = mBmpHeight;
      }
      
      byte tempH = 0;
      while (row < offset)
      {
          byte tempByte = (byte)(0x01 << (tempH & 0x07));
          for (long i = 0; i < mBmpWidth; ++i)
          {
              long curPos = mBmpWidth * row + i;
              byte curPosByte = (byte)(0x80 >> (curPos & 0x07));
              if ((mpBWData[curPos >> 3] & curPosByte) != 0)
              {
                  m3ByteTable[i][tempH >> 3] |= tempByte;
              }
          }
          
          ++row;
          ++tempH;
      }
  }
  
  return m3ByteTable;
}