/************************************************
	���ƣ�ս�������ݿ����ݽṹ����dll��̬�������ļ�
	���ܣ�����dll
	�����ˣ���ԥ��
	����ʱ�䣺2016-2-23
	�汾��1.0
*************************************************/

#ifndef WARHEADDATABASE_GLOBAL_H
#define WARHEADDATABASE_GLOBAL_H

#ifdef WARHEADDATABASE_EXPORTS
#define WARHEADDATABASE_API __declspec(dllexport)
#else
#define WARHEADDATABASE_API __declspec(dllimport)
#endif

// ͷ�ļ�
// ͷ�ļ�
#include <tchar.h>
#include <string>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif // WARHEADDATABASE_GLOBAL_H
