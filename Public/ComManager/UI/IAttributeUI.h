/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性UI接口		                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IATTRIBUTEUI_H_
#define _IATTRIBUTEUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeUI // : public IPluginUI
	{
	public:
		// 析构函数
		virtual ~IAttributeUI() { }
		// 清空所有属性界面
		virtual void Clear(void) = 0;
		// 更改实体
		virtual void ChangeEntity(IEntityBase* pIEntity) = 0;
		// 添加一个实体
		virtual void UpdateNewItem(IAttribute* pIAttribute) = 0;
		// 移除实体
		virtual void UpdateDelItem(IAttribute* pIAttribute) = 0;

	};
}

#endif // _IATTRIBUTEUI_H_