/************************************************************************
	���ƣ��������ģ�鵼��dll��̬�������ļ� MeshSupport_global
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-2-9
	�汾��1.0
************************************************************************/

#ifndef MESHSUPPORT_GLOBAL_H
#define MESHSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef MESHSUPPORT_EXPORTS

#define MESHSUPPORT_API __declspec(dllexport)
#else
#define MESHSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>
#include <string>
#include <math.h>

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