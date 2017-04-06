/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  动态库载入管理		                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef DYLIBMANAGER_H
#define DYLIBMANAGER_H

#pragma once


namespace VR_Soft
{
	class CDyLib;

	class CDyLibManager : public CSingleton<CDyLibManager>
	{
	public:
		explicit CDyLibManager(void);
		virtual ~CDyLibManager(void);

	public:
		// 加载组件
		CDyLib* Load(const VRString& fileName);
		// 卸载组件
		void Unload(CDyLib* pLib);

	private:
		typedef std::map<VRString, CDyLib*> MapStrLib;
		MapStrLib m_mapStrLib;
	};

}

#endif // DYLIBMANAGER_H
