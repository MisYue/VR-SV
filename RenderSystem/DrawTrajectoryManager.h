/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣��Ⱦ����			                                        */
/* ʱ�䣺 2015-08-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _DRAWTRAJECOTORYMANAGER_H_
#define _DRAWTRAJECOTORYMANAGER_H_ 

#pragma once

#include <vector>
#include <osg/Group>

namespace VR_Soft
{
	class CDrawTrajectoryManager : public IDrawTrajectoryManager
	{
	public:
		// ���캯��
		CDrawTrajectoryManager(void);
		// ��������
		virtual ~CDrawTrajectoryManager(void);

	public:
		// ��ӹ켣
		virtual void AddTrajectory(IDrawTrajectory* pIDrawTrajectory) ;
		// �Ƴ��켣
		virtual void RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory) ;
		// ��Ҫ���»���
		virtual void Update(void) ;
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);

	protected:
		// ���
		void Clear(void);

	protected:
		typedef std::vector<IDrawTrajectory*> ListDrawTrajectorys;

	private:
		osg::Group* m_pRoot;

		ListDrawTrajectorys m_listDrawTrajectorys;


	};

}

#endif // !_DRAWTRAJECOTORYMANAGER_H_