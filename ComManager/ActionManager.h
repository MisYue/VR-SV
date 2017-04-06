/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  指令管理类			                                        */
/* 时间： 2016-06-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ACTIONMANAGER_H_
#define _ACTIONMANAGER_H_

#pragma once

#include<boost/unordered_map.hpp>  

namespace VR_Soft
{
	class CActionManager :	public IActionManager
	{
	public:
		// 构造函数
		explicit CActionManager(void);
		// 析构函数
		virtual ~CActionManager(void);

	public:
		// 添加指令
		virtual void AddAction(IEntityBase* pIEnity, const VRString& strAciton) ;
		// 移除指令
		virtual void RemoveAction(IEntityBase* pIEnity, const int index) ;
		// 添加工厂
		virtual void AddFactory(IActionFactory* pIActionFactory) ;
		// 移除工厂
		virtual void RemoveFactory(const VRString& strFactory) ;
		// 从文件中加载指令dll库 
		virtual void LoadAction(void) ;
		// 获取所有的dll指令名称
		virtual ListString GetAllActionDll(void) const ;
		// 获得当前实体的指令
		virtual ListString GetAllActionDll(IEntityBase* pIEntity) const ;
		// 获得指令
		virtual IAction* GetAction(IEntityBase* pIEntity, const int index) const ;
		// 移除dll库
		virtual void RemoveActionDll(const VRString& strDll);
		// 执行指令
		virtual void Execute(const CDateTime& dt) ;
		// 初始化
		virtual void Init(void);

	protected:
		// 导入dll库
		void LoadDll(const VRString& strDllPath);

	private:
	//	ListAction m_listAciton;

		typedef boost::unordered_map<VRString, CDyLib*> ListActionDlls;
		typedef boost::unordered_map<VRString, IActionFactory*> ListActionFactories; 
		typedef std::vector<IAction*> ListAction; // 命令集合
		typedef boost::unordered_map<IEntityBase*, ListAction> ListEntityActions;

		ListActionDlls m_listActionDlls;
		ListActionFactories m_listActionFactorues;
		ListEntityActions m_listEntityAcitons;
		ListAction m_listSimAction; // 循环的指定

		VR_AUTO_MUTEX
	};
}


#endif // !_ACTIONMANAGER_H_