/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  电磁插件管理													*/
/* 时间： 2015-08-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ELECTDLLMANAGER_H_
#define _ELECTDLLMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IEntityFactoryManager;

	class CElectPluginManager : public CSingleton<CElectPluginManager> 
	{
	public:
		explicit CElectPluginManager(IEntityFactoryManager* pIEntityFactoryManager);
		virtual ~CElectPluginManager(void);

		// 查找当前文件下加载插件
		void LoadAllElecDll(void);

	protected:
		// 当前动态库是否加载了
		bool IsLoaded(const VRString& strElecName);
		// 加载单个dll文件
		void LoadElecDll(const VRString& strElecName);
		// 卸载单个dll文件
		void UnLoadElecDll(const VRString& strElecName);
		// 卸载所有的dll文件

		
	protected:
		typedef std::map<VRString, CDyLib*> MapElectPlugin;

	private:
		MapElectPlugin m_mapElectPlugin; // 当前加载的动态库
		IEntityFactoryManager* m_pIEntityFactoryManager; // 实体管理对象
	};
}

#endif // _ELECTDLLMANAGER_H_