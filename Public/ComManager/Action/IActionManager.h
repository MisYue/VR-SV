/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  指令管理接口			                                        */
/* 时间： 2016-06-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IACTIONMANAGER_H_
#define _PUBLIC_IACTIONMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL IActionManager : public CSingleton<IActionManager>
	{
	public: 
		// 析构函数
		virtual ~IActionManager(void) { }
		// 添加指令
		virtual void AddAction(IEntityBase* pIEnity, const VRString& strAciton) = 0;
		// 移除指令
		virtual void RemoveAction(IEntityBase* pIEnity, const int index) = 0;
		// 添加工厂
		virtual void AddFactory(IActionFactory* pIActionFactory) = 0;
		// 移除工厂
		virtual void RemoveFactory(const VRString& strFactory) = 0;
		// 从文件中加载指令dll库 
		virtual void LoadAction(void) = 0;
		// 获取所有的dll指令名称
		virtual ListString GetAllActionDll(void) const = 0;
		// 获得当前实体的指令
		virtual ListString GetAllActionDll(IEntityBase* pIEntity) const = 0;
		// 获得指令
		virtual IAction* GetAction(IEntityBase* pIEntity, const int index) const = 0;
		// 移除dll库
		virtual void RemoveActionDll(const VRString& strDll) = 0;
		// 执行指令
		virtual void Execute(const CDateTime& dt) = 0;
		// 初始化
		virtual void Init( void ) = 0;
	};
}

#endif // !_PUBLIC_IACTIONMANAGER_H_