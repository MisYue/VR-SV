/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类工厂管理接口	                                        */
/* 时间： 2015-07-29                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IENTITYFACTORYMANAGER_H_
#define _IENTITYFACTORYMANAGER_H_

namespace VR_Soft
{
	class IEntityTypeUI;

	class VRSOFT_DLL IEntityFactoryManager : public CSingleton<IEntityFactoryManager>
	{
	public:
		// 析构函数
		virtual ~IEntityFactoryManager() { }
		// 注册工厂
		virtual void RegisterFactory(IEntityBaseFactory* pIEntityFactory) = 0;
		// 卸载工厂
		virtual void UnRegisterFactory(const VRString& strFactoryType) = 0;
		// 获得工厂实例
		virtual IEntityBaseFactory* GetEntityFactory(const VRString& strType) const = 0;
		// 获得工厂列表
		virtual const ListString GetAllEntityFactory(void) const = 0;
		// 添加观察者
		virtual void Attach(IEntityTypeUI* pIEntityTypeUI) = 0;
		// 移除观察者
		virtual void Detach(IEntityTypeUI* pIEntityTypeUI) = 0;
	};
}

#endif // _IENTITYFACTORYMANAGER_H_