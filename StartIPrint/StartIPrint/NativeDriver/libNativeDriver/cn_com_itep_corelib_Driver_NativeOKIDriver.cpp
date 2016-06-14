//
// Created by 辉 on 2016/4/25.
// 
// C++代码需要注意的地方就是，申请的内存需要进行初始化，否则脏内存会干扰图像的解析
// 整数运算注意是否是需要小数，以及导致变0问题
//
#include "cn_com_itep_corelib_Driver_NativeOKIDriver.h"
#include "stdinc.h"
#include "OKIDriver.h"

// void mymemset(byte* pData, byte value, int length)
// {
//   for (int i = 0; i < length; ++i)
//   {
//     *pData = value;
//     ++pData;
//   }
// }

//这里假定传入的BMP格式数据为ARGB
JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeOKIDriver_InnerRemixBmpInOKI
  (JNIEnv *env, jobject obj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData)
{
  int yxPos = -1;
  
  int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
  int BmpDataLength = env->GetArrayLength(bmpData);
  
  byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
  int PrintDataLength = env->GetArrayLength(printData);
  
  OKIDriver okiDriver;
  
  yxPos = okiDriver.InnerRemixBmpInOKI((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength);
  
  return yxPos;
}
