/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������				                                        */
/* ʱ�䣺 2015-05-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ERRORINFO_H_ 
#define _ERRORINFO_H_

namespace VR_Soft
{
#define ERROR_OK				0x00000000 // ����
#define ERROR_MALLOC			0x00000005 // �����ڴ�ʧ��
#define ERROR_EXCEPT			0x00000002 // �����쳣
#define ERROR_MODEL_NULL		0x00000008 // �����쳣
#define ERROR_NOT_FIND			0x00000010 // û���ҵ�
#define ERROR_NOT_EARTH			0x00000012 // earth�ļ�û���ҵ�
#define ERROR_NOT_COM			0x00000014 // ���û���ҵ�
#define ERROR_NOT_ADD			0x00000018 // ���û���ҵ�
#define ERROR_NOT_DRAWABLE		0x00000020 // ��Ⱦ�岻����
#define ERROR_NOT_LONGlAT		0x00000022 // �̲߳�����
#define ERROR_CONVER_FAILD		0x00000024 // �̲߳�����
#define ERROR_NOT_EIDT			0x00000028 // �̲߳�����
#define ERROR_FAILE_CONVERT		0x00000030 // ����ת��ʧ��
#define ERRROR_MESSAGE_NOHANLD  0x00000032 // ��Ϣû����Ӧ
#define ERRROR_NOT_TYPE			0x00000034 // ���Ͳ�һ��
#define ERRROR_HAVEED			0x00000038 // ���Ͳ�һ��
#define ERRROR_OPENFAILD		0x00000040 // ��ʧ��
#define ERROR_ITEM_LOADED		0x00000042 // ��ǰ���Ѿ�����
}
#endif