/************************************************************************
	���ƣ���ҩ������Ϣ���������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-8-21
	�汾��1.0
************************************************************************/

#ifndef BITFUZEDATABASE_GLOBAL_H
#define BITFUZEDATABASE_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITFUZEDATABASE_EXPORTS

#define BITFUZEDATABASE_API __declspec(dllexport)
#else
#define BITFUZEDATABASE_API __declspec(dllimport)
#endif

// ͷ�ļ�
//#include "math.h"
#include <string>

#endif 