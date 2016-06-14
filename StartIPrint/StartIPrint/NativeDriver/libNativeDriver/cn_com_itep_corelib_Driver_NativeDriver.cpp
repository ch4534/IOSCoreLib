//
// Created by 辉 on 2016/4/25.
// 
// C++代码需要注意的地方就是，申请的内存需要进行初始化，否则脏内存会干扰图像的解析
// 整数运算注意是否是需要小数，以及导致变0问题
//
#include "cn_com_itep_corelib_Driver_NativeDriver.h"
#include "stdinc.h"
#include "OKIDriver.h"
#include "OLIDriver.h"
#include "LQDriver.h"
#include "MPDriver.h"
#include "EPOSTPDriver.h"
#include "EPOSADriver.h"

template<typename TD>
int InnerRemixBmp(JNIEnv *env, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
{
   int yxPos = -1;
  
   int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
   int BmpDataLength = env->GetArrayLength(bmpData);
    
   byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
   int PrintDataLength = env->GetArrayLength(printData);
    
   TD driver;
    
   yxPos = driver.InnerRemixBmp((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
    
   env->ReleaseIntArrayElements(bmpData, (jint*)pBmpData, 0);
   env->ReleaseByteArrayElements(printData, (jbyte*)pPrintData, 0);
    
   return yxPos;
}

JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInOKI
  (JNIEnv *env, jclass claj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    // int yxPos = -1;
  
    // int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
    // int BmpDataLength = env->GetArrayLength(bmpData);
    
    // byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
    // int PrintDataLength = env->GetArrayLength(printData);
    
    // OKIDriver okiDriver;
    
    // yxPos = okiDriver.InnerRemixBmp((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
    
    // env->ReleaseIntArrayElements(bmpData, (jint*)pBmpData, 0);
    // env->ReleaseByteArrayElements(printData, (jbyte*)pPrintData, 0);
    
    // return yxPos;
    return InnerRemixBmp<OKIDriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }
  
 JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInOLI
  (JNIEnv *env, jclass claj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    // int yxPos = -1;
  
    // int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
    // int BmpDataLength = env->GetArrayLength(bmpData);
    
    // byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
    // int PrintDataLength = env->GetArrayLength(printData);
    
    // OLIDriver oliDriver;
    
    // yxPos = oliDriver.InnerRemixBmp((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
    
    // env->ReleaseIntArrayElements(bmpData, (jint*)pBmpData, 0);
    // env->ReleaseByteArrayElements(printData, (jbyte*)pPrintData, 0);
    
    // return yxPos;
    
    return InnerRemixBmp<OLIDriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }
  
JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInLQ
  (JNIEnv *env, jclass claj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    // int yxPos = -1;
  
    // int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
    // int BmpDataLength = env->GetArrayLength(bmpData);
    
    // byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
    // int PrintDataLength = env->GetArrayLength(printData);
    
    // LQDriver lqDriver;
    
    // yxPos = lqDriver.InnerRemixBmp((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
    
    // env->ReleaseIntArrayElements(bmpData, (jint*)pBmpData, 0);
    // env->ReleaseByteArrayElements(printData, (jbyte*)pPrintData, 0);
    
    // return yxPos;
    return InnerRemixBmp<LQDriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }
  
  JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInMP
  (JNIEnv *env, jclass claj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    // int yxPos = -1;
  
    // int* pBmpData = (int*)env->GetIntArrayElements(bmpData, 0);
    // int BmpDataLength = env->GetArrayLength(bmpData);
    
    // byte* pPrintData = (byte*)env->GetByteArrayElements(printData, 0);
    // int PrintDataLength = env->GetArrayLength(printData);
    
    // LQDriver lqDriver;
    
    // yxPos = lqDriver.InnerRemixBmp((byte*)pBmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, pPrintData, PrintDataLength, xDPI, yDPI);
    
    // env->ReleaseIntArrayElements(bmpData, (jint*)pBmpData, 0);
    // env->ReleaseByteArrayElements(printData, (jbyte*)pPrintData, 0);
    
    // return yxPos;
    return InnerRemixBmp<MPDriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }
  
  JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInEPOSTP
  (JNIEnv *env, jclass claj, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    return InnerRemixBmp<EPOSTPDriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }
  
  JNIEXPORT jint JNICALL Java_cn_com_itep_corelib_Driver_NativeDriver_InnerRemixBmpInEPOSA
  (JNIEnv *env, jclass clajf, jintArray bmpData, jint bytePerLine, jint bmpWidth, jint bmpHeight, jlong lx, jlong ly, jbyteArray printData, jint xDPI, jint yDPI)
  {
    return InnerRemixBmp<EPOSADriver>(env, bmpData, bytePerLine, bmpWidth, bmpHeight, lx, ly, printData, xDPI, yDPI);
  }