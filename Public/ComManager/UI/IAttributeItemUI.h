/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项控件接口	                                        */
/* 时间： 2015-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLICE_IATTRIBUTEITEMUI_H_
#define _PUBLICE_IATTRIBUTEITEMUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeItemUI
	{
	public:
		// 析构函数
		virtual ~IAttributeItemUI(void) { }
		// 设置信息
		virtual void SetInfor(void) = 0;
		// 改变信息需要保存
		virtual void SaveInfo(void) = 0;
		// 获得类型
		virtual Contrl GetContrlType(void) = 0;
		// 获得控件
		virtual void GetContrl(void* pContrl) = 0;
	};
}

#endif // _PUBLICE_IATTRIBUTEITEMUI_H_