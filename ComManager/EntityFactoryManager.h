/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类工厂管理类	                                        */
/* 时间： 2015-06-09                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ENTITYFACTORYMANAGER_H_
#define _ENTITYFACTORYMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEntityFileManager;

	class CEntityFactoryManager : public IEntityFactoryManager // CSingleton<CEntityFactoryManager>
	{
	public:
		// 构造函数
		explicit CEntityFactoryManager(void);
		// 析构函数
		virtual ~CEntityFactoryManager(void);

		// 注册工厂
		virtual void RegisterFactory(IEntityBaseFactory* pIEntityFactory);
		// 卸载工厂
		virtual void UnRegisterFactory(const VRString& strFactoryType);
		// 获得工厂实例
		virtual IEntityBaseFactory* GetEntityFactory(const VRString& strType) const;
		// 获得工厂列表
		virtual const ListString GetAllEntityFactory(void) const;

	public:
		// 添加观察者
		virtual void Attach(IEntityTypeUI* pIEntityTypeUI);
		// 移除观察者
		virtual void Detach(IEntityTypeUI* pIEntityTypeUI);

	protected:
		// 查找是否存在当前工厂
		bool IsHave(const VRString& strType) const;
		// 删除所有工厂
		void RemoveAll(void);

	protected:
		typedef boost::unordered_map<VRString, IEntityBaseFactory*> ListStrEntityBaseFactories;
		typedef boost::unordered_set<IEntityTypeUI*> ListEntityTypeUIs;
		

	private:
		ListStrEntityBaseFactories m_factorys;
		ListEntityTypeUIs m_listEntityTypeUIs;
		CEntityFileManager* m_pEntityFileManager; // 文件实体类
		VR_AUTO_MUTEX
	};
}


#endif // _ENTITYFACTORYMANAGER_H_
