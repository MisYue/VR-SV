/************************************************************************
	���ƣ���ѧ����ģ�鵼��dll��̬�������ļ� MathcalculationSupport_global
	���ܣ�����dll
	�����ˣ���ԥ�¡�����
	����ʱ�䣺2015-1-26
	�汾��1.0
************************************************************************/

#ifndef MATHCALCULATIONSUPPORT_GLOBAL_H
#define MATHCALCULATIONSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef MATHCALCULATIONSUPPORT_EXPORTS

#define MATHCALCULATIONSUPPORT_API __declspec(dllexport)
#else
#define MATHCALCULATIONSUPPORT_API __declspec(dllimport)
#endif

// ͷ�ļ�
#include <tchar.h>
#include <string>
#include <math.h>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

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


#define pi 3.14159265358979323846			//����Piֵ = 3.1415926
#define radius_earthaverage 6371.004        //�������ƽ���뾶 = 6371.004����λ��km
#define LongAix_Gobe 6378.137               //���������=6378.137����λ��km
#define ShortAix_Gobe 6356.752314           //����������=6356.752314����λ��km
//#define MaxNodeInSS 100000                  //���嵥�����ϵ����ڵ���
//#define GA 9.80665                          //�����������ٶ� 

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H