/************************************************
	���ƣ��������ݿ����ݽṹ����dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ�����
	����ʱ�䣺2015-4-11
	�汾��1.0
*************************************************/

#ifndef MATERIALDATABASE_GLOBAL_H
#define MATERIALDATABASE_GLOBAL_H


#ifdef MATERIALDATABASE_EXPORTS

#define MATERIALDATABASE_API __declspec(dllexport)
#else
#define MATERIALDATABASE_API __declspec(dllimport)
#endif

//ͷ�ļ�
#include <string>
#include <math.h>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif // MATERIALATTRIBUTE_GLOBAL_H