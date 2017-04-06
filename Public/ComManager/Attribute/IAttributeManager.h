/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性管理接口		                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IATTRIBUTEMANAGER_H_
#define _IATTRIBUTEMANAGER_H_

#include "IAttributeItem.h"

namespace VR_Soft
{
	class IAttributeUI;

	class VRSOFT_DLL IAttributeManager : public CSingleton<IAttributeManager>
	{
	public:
		// 析构函数
		virtual ~IAttributeManager() { }
		// 设置当前的属性
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase) = 0;
		// 获得当前激活的实体
		virtual IEntityBase* GetCurrentEntityBase(void) const = 0;
		// 获得当前激活的实体ID
		virtual uint64_t GetCurrentEntityBaseID(void) const  = 0;
		// 编辑当前的实体
		virtual void EidtCurrentEntityBase(void) = 0;
		// 创建属性项对象
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil, \
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX) = 0;
		// 创建属性项对象
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			IProperty* var, bool b , const Contrl ct =  CTRL_SPINBOX) = 0;
		// 更新属性项
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem) = 0;

	public:
		// 添加工厂
		virtual void AddFactory(IAttributeFactory* pIAttributeFactory) = 0;
		// 移除工厂
		virtual void RemoveFactory(const VRString& strFactory) = 0;
		// 获得工厂
		virtual IAttributeFactory* GetFactory(const VRString& strFactory) const = 0;
		// 从文件中加载指令dll库 
		virtual void LoadAttributeDll(void) = 0;
		// 删除所有的库
		virtual void RemoveAllAttributeDll(void) = 0;
		// 移除dll库
		virtual void RemoveAttributeDll(const VRString& strDll) = 0;
		// 获取所有的dll指令名称
		virtual ListString GetAllAttributeDll(void) const = 0;
		// 获得所有属性
		virtual ListString GetAllAttribute(void) const = 0;
		// 绑定实体属性
		virtual bool BindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) = 0;
		// 绑定实体属性
		virtual bool BindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) = 0;
		// 解除绑定
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) = 0;
		// 解除绑定
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) = 0;

	public:
		// 注册界面窗口
		virtual void Attach(IAttributeUI* pIAttributeUI) = 0;
		// 移除观察者
		virtual void Detach(IAttributeUI* pIAttributeUI) = 0;

	};
}

#endif // _IATTRIBUTEMANAGER_H_