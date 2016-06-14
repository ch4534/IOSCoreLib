#ifndef DRIVER_H
#define DRIVER_H

/**
* @brief 驱动抽象类
*/ 
class Driver
{
public:
    Driver();
    virtual ~Driver();  
    
protected:
    //存储空白行，一位代表一行，如果当前位为1，表示为空白行，因为1为true
    byte* mpBlankInfo;
    // byte* mpBlankInfoB;
    //存储灰度图像，每BYTE为一个像素
    byte* mpGrayData; 
    //存储黑白图像，每位代表黑或白，1代表黑点，0代表白色
    byte* mpBWData;
    //表示当前可打印数据的分辨率标识
    byte mESCM; 
    //位图的宽度
    int mBmpWidth;
    //位图的高度
    int mBmpHeight;
    //当前有效的可打印数据字节数
    int myxPos;
    //水平打印分辨率
    int mXDPI;
    //垂直打印分辨率
    int mYDPI;
    
public:
    //解析位图像数数据
    virtual int InnerRemixBmp(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI) = 0;

protected:  
    //双向线性插值算法
    virtual unsigned char Interpolation(byte* lpDIBBits, long lWidth, long lHeight, float x, float y);  
    //获取平均值
    virtual int getMeans(std::vector<int>& data);
    //获取阈值
    virtual int getThreshold(byte* inPixels, int height, int width);
    //将灰度图转换为黑白图
    virtual byte* ConvertToBW(byte* pBmpData, int bmpWidth, int bmpHeight);
    //将ARGB彩色图转换为灰度图
    virtual byte* ConvertToGray(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight);
    //从黑白图数据获取8行数据
    byte** get8Rows(long row);
    //从黑白图数据获取24行数据
    virtual byte** get24Rows(long row);
    //自适应阈值算法
    virtual void WellneradaptiveThreshold2(byte* pData, int width, int height, int bytePerLine, int Radius = 20, int Threshold = 10);
    //判断是否是灰度图
    virtual bool isGrayData(int bmpWidth, int bytePerLine);
    
    //内存释放模板
    template<typename T>
    void releasePointer(T** pointer);
    template<typename T>
    void releasePointers(T** pointer);
};

#endif