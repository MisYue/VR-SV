/************************************************************************
	���ƣ�Ŀ��ģ�͹���ģ�鵼��dll��̬�������ļ�BITTargetModelSupport
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-4-22
	�汾��1.0
************************************************************************/

#ifndef BITTARGETMODELSUPPORT_GLOBAL_H
#define BITTARGETMODELSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITTARGETMODELSUPPORT_EXPORTS

#define BITTARGETMODELSUPPORT_API __declspec(dllexport)
#else
#define BITTARGETMODELSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
// #include <tchar.h>


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