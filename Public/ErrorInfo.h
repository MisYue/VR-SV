/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  错误代码				                                        */
/* 时间： 2015-05-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ERRORINFO_H_ 
#define _ERRORINFO_H_

namespace VR_Soft
{
#define ERROR_OK				0x00000000 // 正常
#define ERROR_MALLOC			0x00000005 // 分配内存失败
#define ERROR_EXCEPT			0x00000002 // 错误异常
#define ERROR_MODEL_NULL		0x00000008 // 错误异常
#define ERROR_NOT_FIND			0x00000010 // 没有找到
#define ERROR_NOT_EARTH			0x00000012 // earth文件没有找到
#define ERROR_NOT_COM			0x00000014 // 组件没有找到
#define ERROR_NOT_ADD			0x00000018 // 组件没有找到
#define ERROR_NOT_DRAWABLE		0x00000020 // 渲染体不存在
#define ERROR_NOT_LONGlAT		0x00000022 // 高程不存在
#define ERROR_CONVER_FAILD		0x00000024 // 高程不存在
#define ERROR_NOT_EIDT			0x00000028 // 高程不存在
#define ERROR_FAILE_CONVERT		0x00000030 // 类型转换失败
#define ERRROR_MESSAGE_NOHANLD  0x00000032 // 消息没有响应
#define ERRROR_NOT_TYPE			0x00000034 // 类型不一致
#define ERRROR_HAVEED			0x00000038 // 类型不一致
#define ERRROR_OPENFAILD		0x00000040 // 打开失败
#define ERROR_ITEM_LOADED		0x00000042 // 当前项已经存在
}
#endif