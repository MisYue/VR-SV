/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  环境模型管理													*/
/* 时间： 2015-11-24                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENRIRONMENTMANAGER_H_
#define _ENRIRONMENTMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEnvironmentManager
	{
	public:
		CEnvironmentManager(IEntityFactoryManager* pIEntityFactoryManager);
		~CEnvironmentManager(void);

		void LoadAllElecDll(void);

	protected:
		// 当前动态库是否加载了
		bool IsLoaded(const VRString& strElecName);
		// 加载单个dll文件
		void LoadElecDll(const VRString& strElecName);
		// 卸载单个dll文件
		void UnLoadElecDll(const VRString& strElecName);

	protected:
		typedef std::map<VRString, CDyLib*> ListEnvironPlugin;

	private:
		ListEnvironPlugin m_lstEnvironPlugins; // 环境
		IEntityFactoryManager* m_pIEntityFactoryManager; // 实体工厂管理对象
	};
}


#endif // !_ENRIRONMENTMANAGER_H_