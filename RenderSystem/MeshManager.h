/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染管理			                                        */
/* 时间： 2016-03-30                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CMeshManager : public CSingleton<CMeshManager>, public IMeshManager
	{
	public:
		CMeshManager(void);
		virtual ~CMeshManager(void);

	public:
		// 获得渲染体
		virtual DrawObj* GetDrawObj(const VRString& strName);
		// 获得所有的渲染体
		virtual const ListMeshObjs GetAllMeshObj(void) const ;

	protected:
		// 初始化
		void Init(void);
		// 读取单个现象值
		VRString GetValue(const VRString& strName);


	private:
		// IMeshManager::ListMeshObjs m_listMeshObjs;
		typedef boost::unordered_map<VRString, MeshObj> ListNameMeshObj;
		ListNameMeshObj m_listNameMeshObj;
	};

}

#endif // !_MESHMANAGER_H_