/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性管理实现类	                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEMANAGER_H_
#define _ATTRIBUTEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IEntityBase;
	/*class IAttribute;*/

	class CAttributeManager : public IAttributeManager
	{
	public:
		// 构造函数
		explicit CAttributeManager(void);
		// 析构函数
		virtual ~CAttributeManager(void);

		// 注册界面窗口
		virtual void RegisterUI(IAttributeUI* pIAttributeUI);
		// 发注册界面窗口
		virtual void UnRegisterUI(IAttributeUI* pIAttributeUI);
		// 设置当前的属性
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase);
		// 添加属性接口
		virtual void AddAttribute(IAttribute* pIAttribute);
		// 创建属性项对象
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX);
		// 更新属性项
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem);

	protected:
		// 更新UI
		void UpdateAttributeUI(const IAttribute* pIAttribute);

	protected:
		typedef std::map<IEntityBase*, IAttribute*> MapEntityAttribute;
		typedef std::vector<IAttributeUI*> VctAttributeUI;

	private:
		MapEntityAttribute m_mapEntityAttribute; // 模型属性列表
		VctAttributeUI m_vecAttributeUI; // 界面集合
		IEntityBase* m_pICurEntityBase; // 当前模型列表

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEMANAGER_H_