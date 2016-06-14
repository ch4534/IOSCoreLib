#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	* @brief OKI仿真解析 当前仅支持 180 * 180 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInOKI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);
	
	/**
	* @brief LQ仿真解析 当前仅支持 180 * 180，360 * 360 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInLQ(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief OLI仿真解析 当前仅支持 180 * 180 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInOLI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief 微打仿真解析 当前仅支持 168 * 144， 84 * 72 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInMP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief 热敏仿真解析 当前仅支持 203 * 203 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInEPOSTP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief 热敏（实达）仿真解析 当前仅支持 300 * 300 打印分辨率的解析
	*
	* @param byte* pBmpData 位图像数数据
	* @param int bytePerLine 每行的字节数（由于位图数据4字节对齐，所以存在 位图数据字节宽度 != 位图宽度 * 每像数占用的字节数）
	* @param int bmpWidth 位图的宽度（即像数个数）
	* @param int bmpHeight 位图的高度
	* @param long lx 水平偏移量
	* @param long ly 垂直偏移量
	* @param byte** pPrintData 可打印数据的缓存
	* @param int PrintDataLength 缓存的长度
	* @param int xDPI 打印水平分辨率
	* @param int yDPI 垂直打印分辨率
	*
	* @return int 返回可打印数据的有效长度
	*/
	EXPORT int InnerRemixBmpInEPOSA(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

#ifdef __cplusplus
}
#endif