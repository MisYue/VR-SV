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
	class CEntityFactoryManager : public IEntityFactoryManager // CSingleton<CEntityFactoryManager>
	{
	public:
		// 构造函数
		explicit CEntityFactoryManager(void);
		// 析构函数
		virtual ~CEntityFactoryManager(void);

		// 注册工厂
		void RegisterFactory(IEntityBaseFactory* pIEntityFactory);
		// 卸载工厂
		void UnRegisterFactory(const VRString& strFactoryType);
		// 获得工厂实例
		IEntityBaseFactory* GetEntityFactory(const VRString& strType) const;
		// 获得工厂列表
		virtual const LstFactroys& GetAllEntityFactory(void) const;

	protected:
		// 查找是否存在当前工厂
		bool IsHave(const VRString& strType) const;
		// 删除所有工厂
		void RemoveAll(void);

	protected:
		

	private:
		LstFactroys m_factorys;

		VR_AUTO_MUTEX
	};
}


#endif // _ENTITYFACTORYMANAGER_H_
