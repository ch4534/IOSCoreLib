#include "stdinc.h"
#include "Driver.h"

Driver::Driver()
{
    mpGrayData = nullptr;
    mpBlankInfo = nullptr;
    // mpBlankInfoB = nullptr;
    mBmpWidth = 0;
    mBmpHeight = 0;
    myxPos = 0;
    mESCM = 0x27;
    mXDPI = 180;
    mYDPI = 180;
}

Driver::~Driver()
{
    releasePointers(&mpGrayData);
    releasePointers(&mpBlankInfo);
    // releasePointers(&mpBlankInfoB);
    releasePointers(&mpBWData);
}

template<typename T>
void releasePointer(T** pointer)
{
    if ((*pointer) != nullptr)
    {
        delete (*pointer);
        (*pointer) = nullptr;
    }
}

template<typename T>
void Driver::releasePointers(T** pointer)
{
     if ((*pointer) != nullptr)
     {
         delete[] (*pointer);
         (*pointer) = nullptr;
     }
}

/**
* @brief 获取8行可打印机黑白图数据
*
* @param long row 所需要获取的行数
*
* @return 返回8行的结果，每个字节一位表示一行
*/
byte** Driver::get8Rows(long row)
{
    byte** mByteTable = nullptr;
    
    if (row < mBmpHeight)
    {
        mByteTable = new byte*[mBmpWidth];
        for (long i = 0; i < mBmpWidth; ++i)
        {
            mByteTable[i] = new byte[1];
            mByteTable[i][0] = 0x00;
        }
        
        long offset = row + 8;
        if (offset > mBmpHeight)
        {
            offset = mBmpHeight;
        }
        
        byte tempH = 0;
        while (row < offset)
        {
            //每八行循环右移0x80，用于与返回值或运算
            byte tempByte = (byte)(0x80 >> (tempH & 0x07));
            for (long i = 0; i < mBmpWidth; ++i)
            {
                //根据行列获取当前像素点的位置
                long curPos = mBmpWidth * row + i;
                //根据计算的位置，循环右移0X80，直到当前像数位置所在字节的那一位上
                byte curPosByte = (byte)(0x80 >> (curPos & 0x07));
                //从mpBWData中取到当前位置所在的字节（由于像数以位存储，所以需要右移3位，也就是除以8）
                //取到字节位置后，与curPosByte与运算获取当前位的结果，不等于0表示有黑点
                if ((mpBWData[curPos >> 3] & curPosByte) != 0)
                {
                    mByteTable[i][0] |= tempByte; 
                }
            }
            
            //切换到下一行
            ++row;
            ++tempH;
        }
    }
    
    //返回相熟黑白数据
    return mByteTable;
}

/**
* @biref 获取25行可打印黑白数据
*
* @param long row 获取的起始行数
*
* @return byte** 返回24行的结果，每个字节一位表示一行
*/
byte** Driver::get24Rows(long row)
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
          byte tempByte = (byte)(0x80 >> (tempH & 0x07));
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

/**
* @biref 将ARGB彩色位图像数裸数据转换为灰度图数据
*
* @param byte* pBmpData 传入ARGB彩色裸数据
* @param int bytePerLine 裸数据每行的字节空间（由于像数数据需要4字节对齐，所以每行字节数与像数宽度并不一定一样）
* @param int bmpWidth 图像的逻辑宽度
* @param int bmpHeight 图像的高度
*
* @return byte* 返回灰度值，每个字节代表一个像数
*/
byte* Driver::ConvertToGray(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight)
{
  byte* pGrayData = new byte[bmpHeight * bmpWidth];
  memset(pGrayData, 0, bmpHeight * bmpWidth);
  
  for (int i = 0; i < bmpHeight; ++i)
  {
    for (int j = 0; j < bmpWidth; ++j)
    {
      byte r = pBmpData[i * bytePerLine + 4 * j + 1];
      byte g = pBmpData[i * bytePerLine + 4 * j + 2];
      byte b = pBmpData[i * bytePerLine + 4 * j + 3];
      
      byte gray = (r * 299 + g * 587 + b * 114 + 500) / 1000;
      
      pGrayData[i * bmpWidth + j] = gray;
    }
  }
  
  return pGrayData;
}

/**
* @biref 将灰度值转换为黑白位值存储起来
*
* @param byte* pBmpData 传入灰度裸数据
* @param int bmpWidth 传入裸数据的宽度字节
* @param int bmpHeight 传入裸数据的高度字节
*
* @return byte* 返回黑白位值
*/
byte* Driver::ConvertToBW(byte* pBmpData, int bmpWidth, int bmpHeight)
{
#ifdef _MSC_VER
  this->WellneradaptiveThreshold2(pBmpData, bmpWidth, bmpHeight, bmpWidth);
  
  //计算以位存储空白行信息需要多少个字节
  int count = bmpHeight / 8 + bmpHeight % 8;
  byte* pBlankInfo = new byte[count];
  memset(pBlankInfo, 0, count);
  
  //计算以位存储黑白像数信息需要多少个字节
  int countPixels = bmpWidth * bmpHeight;
  count = countPixels / 8 + countPixels % 8;
  byte* bmpData = new byte[count];
  memset(bmpData, 0, count);
  
  for (int y = 0; y < bmpHeight; ++y)
  {
    bool isBlank = true;
    for (int x = 0; x < bmpWidth; ++x)
    {
      //获取当前像数位置
      long curPos = y * bmpWidth + x;
      if (pBmpData[curPos] > 128)
      {
        // pBmpData[y * bmpWidth + x] = 255;
      }
      else
      {
        isBlank = false;
        // pBmpData[curPos] = 0;
        //计算当前位置所在的字节所在的位位置
        byte tempByte = (byte)(0x80 >> (curPos & 0x07));
        //将当前位 位置 置为1
        bmpData[curPos >> 3] |= tempByte;
      }
    }
    
    //如果isBlank为true，表示为空白行，那么将当前高度位位置设置为1
    if (isBlank){
        byte tempByte = (byte)(0x80 >> (y & 0x07));
        pBlankInfo[y >> 3] |= tempByte;
    }
  }
  
#else
  int tinyWidth = 64;
  int tinyHeight = 64;
  
  byte* pNewData = new byte[tinyHeight * tinyWidth];
  memset(pNewData, 0, tinyHeight * tinyWidth);
  
  //利用双线性插值算法得到一张64*64像数的灰度图像
  float a = 0, b = 0;
  for (int y = 0; y < tinyHeight; ++y)
  {
    for (int x = 0; x < tinyWidth; ++x)
    {
       a = ((float)x + 0.5f) * (float)bmpWidth / (float)tinyWidth - 0.5f;
       b = ((float)y + 0.5f) * (float)bmpHeight /(float)tinyHeight - 0.5f;
       
       byte gray = Interpolation(pBmpData, bmpWidth, bmpHeight, a, b);
       
       pNewData[y * tinyWidth + x] = gray;
    }
  } 
  
  //利用OSTU算法计算缩略图的阈值
  int threshold = getThreshold(pNewData, tinyWidth, tinyHeight);
#ifdef __ANDROID__
  __android_log_print(ANDROID_LOG_DEBUG, "NativeOKIDriver", "threshold is %d", threshold);
#endif
  
//   delete[] pNewData;
  releasePointers(&pNewData);
  
  //计算以位存储空白行信息需要多少个字节
  int count = bmpHeight / 8 + bmpHeight % 8;
  byte* pBlankInfo = new byte[count];
  memset(pBlankInfo, 0, count);
  
  //计算以位存储黑白像数信息需要多少个字节
  int countPixels = bmpWidth * bmpHeight;
  count = countPixels / 8 + countPixels % 8;
  byte* bmpData = new byte[count];
  memset(bmpData, 0, count);
  
  for (int y = 0; y < bmpHeight; ++y)
  {
    bool isBlank = true;
    for (int x = 0; x < bmpWidth; ++x)
    {
      //获取当前像数位置
      long curPos = y * bmpWidth + x;
      if (pBmpData[curPos] > threshold)
      {
        // pBmpData[y * bmpWidth + x] = 255;
      }
      else
      {
        isBlank = false;
        // pBmpData[curPos] = 0;
        //计算当前位置所在的字节所在的位位置
        byte tempByte = (byte)(0x80 >> (curPos & 0x07));
        //将当前位 位置 置为1
        bmpData[curPos >> 3] |= tempByte;
      }
    }
    
    //如果isBlank为true，表示为空白行，那么将当前高度位位置设置为1
    if (isBlank){
        byte tempByte = (byte)(0x80 >> (y & 0x07));
        pBlankInfo[y >> 3] |= tempByte;
    }
  }
  
#endif

  //存储黑白像数内存
  mpBWData = bmpData;
  
  //返回高度位空白行信息
  return pBlankInfo;
}

/**
* @biref 获取阈值
*
* @param byte* inPixels 灰度像数内存
* @param int height 灰度像数高度
* @param int width 灰度像数宽度
*
* @return int 返回计算的阈值结果
*/
int Driver::getThreshold(byte* inPixels, int height, int width)
 {
        // maybe this value can reduce the calculation consume;
        int inithreshold = 127;
        int finalthreshold = 0;
        int count = width * height;
        int* temp = new int[count];
        memset(temp, 0, count);
        for(int index = 0; index < count; index++)
        {
            temp[index] = inPixels[index];
        }
        std::vector<int> sub1;
        std::vector<int> sub2;
        int means1 = 0, means2 = 0;
        while(finalthreshold != inithreshold) {
            finalthreshold = inithreshold;
            for(int i=0; i<count; i++) {
                if(temp[i]>65536/2){
                    
                }
                if(temp[i] <= inithreshold) {
                    sub1.push_back(temp[i]);
                } else {
                    sub2.push_back(temp[i]);
                }
            }
            means1 = getMeans(sub1);
            means2 = getMeans(sub2);
            sub1.clear();
            sub2.clear();
            inithreshold = (means1 + means2) / 2;
        }
        
        delete[] temp;
        
        return finalthreshold;
 }

/**
* @biref 计算像数平均值
*
* @param std::vector<int>& data 传入存储相应灰度像数的个数
*
* @return int 返回平均值
*/
int Driver::getMeans(std::vector<int>& data)
{
        int result = 0;
        int size = data.size();
        for(int i : data) {
            result += i;
        }
        return (result/size);
}


/*************************************************************************
* 函数名称：
*   Interpolation()
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   long  lWidth       - 源图像宽度（像素数）
*   long  lHeight      - 源图像高度（像素数）
*   float x			- 插值元素的x坐标
*   float y		    - 插值元素的y坐标
* 返回值:
*   unsigned char      - 返回插值计算结果。
* 说明:
*   该函数利用双线性插值算法来估算像素值。对于超出图像范围的像素，
* 直接返回255。
************************************************************************/
unsigned char Driver::Interpolation (byte* lpDIBBits, long lWidth,
                             long lHeight, float x, float y)
{
    // 四个最临近像素的坐标(i1, j1), (i2, j1), (i1, j2), (i2, j2)
    long	i1, i2;
    long	j1, j2;

    unsigned char	f1, f2, f3, f4;	// 四个最临近像素值
    unsigned char	f12, f34;		// 二个插值中间值

    // 定义一个值，当像素坐标相差小于改值时认为坐标相同
    float			EXP;

    long lLineBytes;				// 图像每行的字节数
    lLineBytes = WIDTHBYTES(lWidth * 8);

    EXP = (float) 0.0001;

    // 计算四个最临近像素的坐标
    i1 = (long) x;
    i2 = i1 + 1;
    j1 = (long) y;
    j2 = j1 + 1;

    // 根据不同情况分别处理
    if( (x < 0) || (x > lWidth - 1) || (y < 0) || (y > lHeight - 1))
    {
        return 255;		// 要计算的点不在源图范围内，直接返回255。
    }
    else
    {
        if (fabs(x - lWidth + 1) <= EXP)
        {
            // 要计算的点在图像右边缘上
            if (fabs(y - lHeight + 1) <= EXP)
            {
                // 要计算的点正好是图像最右下角那一个像素，直接返回该点像素值
                f1 = *((unsigned char *)lpDIBBits + lLineBytes *
                    (/*lHeight - 1 - */j1) + i1);
                return f1;
            }
            else
            {
                // 在图像右边缘上且不是最后一点，直接一次插值即可
                f1 = *((unsigned char *)lpDIBBits + lLineBytes *
                    (/*lHeight - 1 - */j1) + i1);
                f3 = *((unsigned char *)lpDIBBits + lLineBytes *
                    (/*lHeight - 1 - */j1) + i2);

                // 返回插值结果
                return ((unsigned char) (f1 + (y -j1) * (f3 - f1)));
            }
        }
        else if (fabs(y - lHeight + 1) <= EXP)
        {
            // 要计算的点在图像下边缘上且不是最后一点，直接一次插值即可
            f1 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j1) + i1);
            f2 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j2) + i1);

            // 返回插值结果
            return ((unsigned char) (f1 + (x -i1) * (f2 - f1)));
        }
        else
        {
            // 计算四个最临近像素值
            f1 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j1) + i1);
            f2 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j2) + i1);
            f3 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j1) + i2);
            f4 = *((unsigned char*)lpDIBBits + lLineBytes * (/*lHeight - 1 - */j2) + i2);

            // 插值1
            f12 = (unsigned char) (f1 + (x - i1) * (f2 - f1));
            // 插值2
            f34 = (unsigned char) (f3 + (x - i1) * (f4 - f3));
            // 插值3
            return ((unsigned char) (f12 + (y -j1) * (f34 - f12)));
        }
    }
}

/**
* @brief 使用自适应二值化方法
*
* @param byte* pData 仅处理8位图的数据
* @param int width 位图的宽度
* @param int height 位图的高度
* @param int bytePerLine 每行的字节数（8位图应该与位图的宽度相等）
* @param int Radius = 20 范围0~255 每个像素二值化时，参考像素的范围
* @param int Threshold = 10 范围0~100，值越靠近于0，图像的黑色越明显，值于靠近于100，图像的黑色越不明显
*/
void Driver::WellneradaptiveThreshold2(byte* pData, int width, int height, int bytePerLine, int Radius, int Threshold)
{
	if (Radius < 0 || Radius > 255)
	{
		return;
	}

	if (Threshold < 0 || Threshold > 100)
	{
		return;
	}

	int Sum, X1, X2, Y1, Y2, Y2Y1;
	byte* Pointer = pData;   //指向像素数据的指针
	int Width = width;       //图片的宽度
	int Height = height;     //图片的高度
	int Stride = bytePerLine;//每行像素数据的字节数
	int InvertThreshold = 100 - Threshold;
	int* Integral = new int[Width * Height * 4];
	int* IndexOne;
	int* IndexTwo;

	//扫描每行的像素值存储在新申请的内存中
	//首行数据只需要做到单行关联即可
	//其他行数据需要做到前行关联
	for (int Y = 0; Y < Height; Y++)
	{
		Sum = 0;
		Pointer = pData + Stride * Y;
		IndexOne = Integral + Width * Y;
		for (int X = 0; X < Width; X++)
		{
			Sum += *Pointer;
			if (Y == 0)
				*IndexOne = Sum;
			else
				*IndexOne = *(IndexOne - Width) + Sum;
			IndexOne++;
			Pointer++;
		}
	}

	for (int Y = 0; Y < Height; Y++)
	{
		Pointer = pData + Stride * Y;
		Y1 = Y - Radius; 
		Y2 = Y + Radius;
		if (Y1 < 0)
		{
			Y1 = 0;
		}
		if (Y2 >= Height)
		{
			Y2 = Height - 1;
		}

		IndexOne = Integral + Y1 * Width;
		IndexTwo = Integral + Y2 * Width;
		Y2Y1 = (Y2 - Y1) * 100;
		for (int X = 0; X < Width; X++)
		{
			X1 = X - Radius;
			X2 = X + Radius;
			if (X1 < 0)
			{
				X1 = 0;
			}

			if (X2 >= Width)
			{
				X2 = Width - 1;
			}

			Sum = *(IndexTwo + X2) - *(IndexOne + X2) - *(IndexTwo + X1) + *(IndexOne + X1);
			if (*Pointer * (X2 - X1) * Y2Y1 < Sum * InvertThreshold)
				*Pointer = 0;
			else
				*Pointer = 255;
			Pointer++;
		}
	}
	delete[] Integral;
}

bool Driver::isGrayData(int bmpWidth, int bytePerLine)
{
    if ((bmpWidth - bytePerLine) < 4 || (bmpWidth - bytePerLine) > -4)
    {
        return true;
    }
    else
    {
        return false;
    }
}