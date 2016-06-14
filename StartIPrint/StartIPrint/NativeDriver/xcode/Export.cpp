#include "../libNativeDriver/stdinc.h"
#include "../libNativeDriver/stdinc.h"
#include "../libNativeDriver/OKIDriver.h"
#include "../libNativeDriver/EPOSADriver.h"
#include "../libNativeDriver/EPOSTPDriver.h"
#include "../libNativeDriver/LQDriver.h"
#include "../libNativeDriver/OLIDriver.h"
#include "../libNativeDriver/MPDriver.h"
#include "Export.h"

template<typename TD>
int InnerRemixBmp(byte* bmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* printData, int PrintDataLength, int xDPI, int yDPI)
{
	int yxPos = -1;

	TD driver;

	yxPos = driver.InnerRemixBmp(bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, PrintDataLength, xDPI, yDPI);

	return yxPos;
}

int InnerRemixBmpInOKI(unsigned char* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, unsigned char* pPrintData, int PrintDataLength, int xDPI, int yDPI)
{
    return InnerRemixBmp<OKIDriver>(pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
}