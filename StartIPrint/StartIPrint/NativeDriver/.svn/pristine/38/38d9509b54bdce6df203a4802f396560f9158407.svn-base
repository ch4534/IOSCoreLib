#include "msvcinc.h"
#include "../../libNativeDriver/stdinc.h"
#include "../../libNativeDriver/OKIDriver.h"
#include "../../libNativeDriver/EPOSADriver.h"
#include "../../libNativeDriver/EPOSTPDriver.h"
#include "../../libNativeDriver/LQDriver.h"
#include "../../libNativeDriver/OLIDriver.h"
#include "../../libNativeDriver/MPDriver.h"
#include "Export.h"

template<typename TD>
int InnerRemixBmp(byte* bmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* printData, int PrintDataLength, int xDPI, int yDPI)
{
	int yxPos = -1;

	TD driver;

	yxPos = driver.InnerRemixBmp(bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, PrintDataLength, xDPI, yDPI);

	return yxPos;
}

int InnerRemixBmpInOKI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<OKIDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}

int InnerRemixBmpInLQ(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<LQDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}

int InnerRemixBmpInOLI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<OLIDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}

int InnerRemixBmpInMP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<MPDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}

int InnerRemixBmpInEPOSTP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<EPOSTPDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}

int InnerRemixBmpInEPOSA(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
	return InnerRemixBmp<EPOSADriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}
