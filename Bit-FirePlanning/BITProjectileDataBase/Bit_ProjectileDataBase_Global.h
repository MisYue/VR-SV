/************************************************************************
	���ƣ���ҩ��Ϣ���������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-8-21
	�汾��1.0
************************************************************************/

#ifndef BITPROJECTILEDATABASE_GLOBAL_H
#define BITPROJECTILEDATABASE_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITPROJECTILEDATABASE_EXPORTS

#define BITPROJECTILEDATABASE_API __declspec(dllexport)
#else
#define BITPROJECTILEDATABASE_API __declspec(dllimport)
#endif

// ͷ�ļ�
//#include "math.h"
#include <string>

#endif 