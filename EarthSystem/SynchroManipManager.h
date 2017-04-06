/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  同步操作器管理类	                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SYNCHROMANIPMANNAGER_H_
#define _SYNCHROMANIPMANNAGER_H_

#pragma once

#include <vector>
#include "SynchroManipulator.h"


namespace VR_Soft
{
	class CSynchroManipManager : public ISynchroManIpManager
	{
	public:
		CSynchroManipManager(void);
		virtual ~CSynchroManipManager(void);

	public:
		// 设置视点
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// 获得视点
		virtual osgEarth::Viewpoint GetViewPoint(void) const ;
		// 跟踪实体模型
		virtual void SetTrackEntity(const uint64_t uID) ;
		// 断开跟踪模型
		virtual void BreakTrackEntity(void) ;
		

	public:
		// 设置视点
		void SetViewPoint(const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// 设置原始视点
		void SetHomeViewPoint(const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// 设置距离
		void SetDistance(const CSynchroManipulator* pSynchroManip, const double dDistance );

	public:
		// 添加操作器
		void Add(CSynchroManipulator* pSynchorManipulator);
		// 移除操作器
		void Remove(CSynchroManipulator* pSynchorManipulator);

	protected:
		// 移除所有操作器
		void RemoveAll(void);
		
	private:
		typedef std::vector<CSynchroManipulator*> ListSynchroManipulators;

		ListSynchroManipulators m_listSynchroManipulators;
	};

}

#endif // !_SYNCHROMANIPMANNAGER_H_