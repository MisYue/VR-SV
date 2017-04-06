/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  路径管理类头文件		                                        */
/* 时间： 2016-06-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PATHMANAGER_H_
#define _PATHMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CPathManager : public IPathManager
	{
	public:
		// 构造函数
		CPathManager(void);
		// 析构函数
		virtual ~CPathManager(void);

	public:
		// 添加路径
		virtual IPath* Create(const uint64_t uID, const VRString& strName, IFeatureGeomtry* pIFeatureGeomtry, IPathStrategy* pIPathStragey = NULL) ;
		// 移除路径
		virtual void Remove(const uint64_t uID) ;
		// 查询路径
		virtual IPath* GetPath(const uint64_t uID) const ;
		// 查询路径通过名称
		virtual std::vector<IPath*> GetPath(const VRString& strName) const ;
		// 获得所有路径
		virtual std::vector<IPath*> GetAllPath(void) const;

	protected:
		// hash 存储路径
		typedef boost::unordered_map<const uint64_t, IPath*> ListIDPath;

		// 移除所有的
		void RemoveAll(void);

	private:
		ListIDPath m_listIDPath; // 路径集合
	};
}


#endif // !_PATHMANAGER_H_