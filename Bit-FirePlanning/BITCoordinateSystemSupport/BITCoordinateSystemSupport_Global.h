/************************************************************************
	���ƣ�����ϵ֧��ģ�鵼��dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-3-20
	�汾��1.0
************************************************************************/

#ifndef BITCOORDINATESYSTEMSUPPORT_GLOBAL_H
#define BITCOORDINATESYSTEMSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITCOORDINATESYSTEMSUPPORT_EXPORTS

#define BITCOORDINATESYSTEMSUPPORT_API __declspec(dllexport)
#else
#define BITCOORDINATESYSTEMSUPPORT_API __declspec(dllimport)
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