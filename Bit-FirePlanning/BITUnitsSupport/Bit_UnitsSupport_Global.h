/************************************************************************
	���ƣ���λ��֧��ģ�鵼��dll��̬�������ļ�BITUnitsSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-6-21
	�汾��1.0
************************************************************************/

#ifndef BITUNITSSUPPORT_GLOBAL_H
#define BITUNITSSUPPORT_GLOBAL_H

#ifdef BITUNITSSUPPORT_EXPORTS

#define BITUNITSSUPPORT_API __declspec(dllexport)
#else
#define BITUNITSSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
#include <math.h>


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926
//// ������ַ���
//#ifdef UNICODE
//typedef wchar_t BITSimChar;
//typedef std::wstring BITSimStr;
//#define BITSimStrlen wcslen  // ȡ�ÿ��ֽ��ַ������ַ����ȣ������� '/0'
//#define BITMemcpy wmemcpy    // ���ֽڵĿ���
//#define _T(x) L##x         // ���ַ���������
//#else
//	
//#endif

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H