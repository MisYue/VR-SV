/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备插件管理													*/
/* 时间： 2015-08-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _AIRLINEMANAGER_H_
#define _AIRLINEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CAirLineManager
	{
	public:
		explicit CAirLineManager(IEntityFactoryManager* pIEntityFactoryManager);
		virtual ~CAirLineManager(void);

		// 查找当前文件下加载插件
		void LoadAllElecDll(void);

	protected:
		// 当前动态库是否加载了
		bool IsLoaded(const VRString& strElecName);
		// 加载单个dll文件
		void LoadElecDll(const VRString& strElecName);
		// 卸载单个dll文件
		void UnLoadElecDll(const VRString& strElecName);

	protected:
		typedef std::map<VRString, CDyLib*> ListEquipPlugin;

	private:
		ListEquipPlugin m_lstEquipPlugin; // 装备
		IEntityFactoryManager* m_pIEntityFactoryManager; // 实体工厂管理对象
	};
}


#endif // !_AIRLINEMANAGER_H_