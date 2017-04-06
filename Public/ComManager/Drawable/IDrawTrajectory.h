/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣��Ⱦ�������		                                        */
/* ʱ�䣺 2016-03-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORYMANAGER_H_
#define _PUBLICE_IDRAWTRAJECTORYMANAGER_H_

namespace VR_Soft
{
	class IDrawTrajectory;

	class IDrawTrajectoryManager
	{
	public:
		// ��������
		virtual ~IDrawTrajectoryManager(void) { }
		// ��ӹ켣
		virtual void AddTrajectory(IDrawTrajectory* pIDrawTrajectory) = 0;
		// �Ƴ��켣
		// ��ӹ켣
		virtual void RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory) = 0;
		// ��Ҫ���»���
		virtual void Update(void) = 0;
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void) = 0;
		
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORYMANAGER_H_