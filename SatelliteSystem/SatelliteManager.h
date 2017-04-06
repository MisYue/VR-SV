/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星模型管理													*/
/* 时间： 2015-11-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _SATELLITEMANAGER_H_
#define _SATELLITEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteManager
	{
	public:
		explicit CSatelliteManager(void);
		virtual ~CSatelliteManager(void);

		void LoadAllElecDll(void);

	protected:
		// 当前动态库是否加载了
		bool IsLoaded(const VRString& strElecName);
		// 加载单个dll文件
		void LoadElecDll(const VRString& strElecName);
		// 卸载单个dll文件
		void UnLoadElecDll(const VRString& strElecName);

	};

}

#endif