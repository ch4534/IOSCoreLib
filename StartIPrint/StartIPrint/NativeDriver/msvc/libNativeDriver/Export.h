#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	* @brief OKI������� ��ǰ��֧�� 180 * 180 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInOKI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);
	
	/**
	* @brief LQ������� ��ǰ��֧�� 180 * 180��360 * 360 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInLQ(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief OLI������� ��ǰ��֧�� 180 * 180 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInOLI(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief ΢�������� ��ǰ��֧�� 168 * 144�� 84 * 72 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInMP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief ����������� ��ǰ��֧�� 203 * 203 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInEPOSTP(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

	/**
	* @brief ������ʵ�������� ��ǰ��֧�� 300 * 300 ��ӡ�ֱ��ʵĽ���
	*
	* @param byte* pBmpData λͼ��������
	* @param int bytePerLine ÿ�е��ֽ���������λͼ����4�ֽڶ��룬���Դ��� λͼ�����ֽڿ�� != λͼ��� * ÿ����ռ�õ��ֽ�����
	* @param int bmpWidth λͼ�Ŀ�ȣ�������������
	* @param int bmpHeight λͼ�ĸ߶�
	* @param long lx ˮƽƫ����
	* @param long ly ��ֱƫ����
	* @param byte** pPrintData �ɴ�ӡ���ݵĻ���
	* @param int PrintDataLength ����ĳ���
	* @param int xDPI ��ӡˮƽ�ֱ���
	* @param int yDPI ��ֱ��ӡ�ֱ���
	*
	* @return int ���ؿɴ�ӡ���ݵ���Ч����
	*/
	EXPORT int InnerRemixBmpInEPOSA(byte* pBmpData, int bytePerLine, int bmpWidth, int bmpHeight, long lx, long ly, byte* pPrintData, int PrintDataLength, int xDPI, int yDPI);

#ifdef __cplusplus
}
#endif