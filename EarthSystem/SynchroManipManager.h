/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ͬ��������������	                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
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
		// �����ӵ�
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// ����ӵ�
		virtual osgEarth::Viewpoint GetViewPoint(void) const ;
		// ����ʵ��ģ��
		virtual void SetTrackEntity(const uint64_t uID) ;
		// �Ͽ�����ģ��
		virtual void BreakTrackEntity(void) ;
		

	public:
		// �����ӵ�
		void SetViewPoint(const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// ����ԭʼ�ӵ�
		void SetHomeViewPoint(const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// ���þ���
		void SetDistance(const CSynchroManipulator* pSynchroManip, const double dDistance );

	public:
		// ��Ӳ�����
		void Add(CSynchroManipulator* pSynchorManipulator);
		// �Ƴ�������
		void Remove(CSynchroManipulator* pSynchorManipulator);

	protected:
		// �Ƴ����в�����
		void RemoveAll(void);
		
	private:
		typedef std::vector<CSynchroManipulator*> ListSynchroManipulators;

		ListSynchroManipulators m_listSynchroManipulators;
	};

}

#endif // !_SYNCHROMANIPMANNAGER_H_