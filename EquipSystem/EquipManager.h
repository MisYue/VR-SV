/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备插件管理													*/
/* 时间： 2015-08-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _EQUIPMANAGER_H_
#define _EQUIPMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEquipManager
	{
	public:
		explicit CEquipManager(IEntityFactoryManager* pIEntityFactoryManager);
		virtual ~CEquipManager(void);

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


#endif // !_EQUIPMANAGER_H_