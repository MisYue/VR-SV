/************************************************************************
���ƣ�ײ���뱬ը����ģ�鵼��dll��̬�������ļ� HitAndExplsionPointAnalysis_Glod
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-1-26
	�汾��1.0
************************************************************************/



#ifndef HITANDEXPLSIONPOINTANALYSIS_GLOBAL_H
#define HITANDEXPLSIONPOINTANALYSIS_GLOBAL_H

#define HITANDEXPLSIONPOINTANALYSIS_EXPORTS
#ifdef HITANDEXPLSIONPOINTANALYSIS_EXPORTS

#define HITANDEXPLSIONPOINTANALYSIS_API __declspec(dllexport)
#else
#define HITANDEXPLSIONPOINTANALYSIS_API __declspec(dllimport)
#endif

// ͷ�ļ�
#include <string>

#endif

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

 