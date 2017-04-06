/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性管理实现类	                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEMANAGER_H_
#define _ATTRIBUTEMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

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

		// 设置当前的属性
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase);
		// 获得当前激活的实体
		virtual IEntityBase* GetCurrentEntityBase(void) const ;
		// 获得当前激活的实体ID
		virtual uint64_t GetCurrentEntityBaseID(void) const ;
		// 编辑当前的实体
		virtual void EidtCurrentEntityBase(void) ;
		// 创建属性项对象
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX);
		// 创建属性项对象
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			IProperty* var, bool b , const Contrl ct =  CTRL_SPINBOX);
		// 更新属性项
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem);

	public:
		// 添加工厂
		virtual void AddFactory(IAttributeFactory* pIAttributeFactory) ;
		// 移除工厂
		virtual void RemoveFactory(const VRString& strFactory) ;
		// 获得工厂
		virtual IAttributeFactory* GetFactory(const VRString& strFactory) const;
		// 从文件中加载指令dll库 
		virtual void LoadAttributeDll(void);
		// 删除所有的库
		virtual void RemoveAllAttributeDll(void) ;
		// 移除dll库
		virtual void RemoveAttributeDll(const VRString& strDll) ;
		// 获取所有的dll指令名称
		virtual ListString GetAllAttributeDll(void) const ;
		// 获得所有属性
		virtual ListString GetAllAttribute(void)  const;
		// 绑定实体属性
		virtual bool BindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory);
		// 绑定实体属性
		virtual bool BindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) ;
		// 接触绑定
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) ;
		// 解除绑定
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) ;

	public:
		// 注册界面窗口
		virtual void Attach(IAttributeUI* pIAttributeUI);
		// 移除观察者
		virtual void Detach(IAttributeUI* pIAttributeUI);

	protected:
		// 更新UI
		void UpdateAttributeUI(IEntityBase* pIEntityBase);
		// 导入dll库
		void LoadDll(const VRString& strDllPath);
		// 初始化
		void Init(void);
		// 移除所有的属性工厂
		void RemoveAllFactory(void);
	protected:
// 		typedef std::map<IEntityBase*, IAttribute*> MapEntityAttribute;
 		typedef boost::unordered_set<IAttributeUI*> VctAttributeUI;

		typedef boost::unordered_map<VRString, CDyLib*> ListAttributeDlls; // dll 对应集合
		typedef boost::unordered_map<VRString, IAttributeFactory*> ListAttributeFactories;  // 工厂集合
		typedef std::vector<uint64_t> ListEntities; // 工厂ID属性
		typedef boost::unordered_map<IAttributeFactory*, ListEntities> ListAttributeFactoriesEntities; // 工厂对应的实体

	private:
//		MapEntityAttribute m_mapEntityAttribute; // 模型属性列表
		VctAttributeUI m_vecAttributeUI; // 界面集合
		uint64_t m_uCurrentID; // IEntityBase* m_pICurEntityBase; // 当前模型列表

		ListAttributeDlls m_listAttributeDlls;
		ListAttributeFactories m_listAttributeFactories; // 工厂集合
		ListAttributeFactoriesEntities m_listAttributeFactoriesEntities; // 工厂对应的实体

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEMANAGER_H_