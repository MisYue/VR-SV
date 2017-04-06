/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣ʵ��ӿ�			                                        */
/* ʱ�䣺 2015-08-04                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITRAJECTORYENTITY_H_
#define _PUBLIC_ITRAJECTORYENTITY_H_

#include <vector>

namespace VR_Soft
{
	class ITrajectoryEntity : public CEntityBaseImp<IEntityBase>
	{
	public: 
		// ��������
		virtual ~ITrajectoryEntity(void) { }
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		// ����㷨����
		virtual ITrajectory* GetTrajectory(void) = 0;
		// ���ɹ��
		virtual void Generate(void) = 0;
	};
	
}

#endif // _PUBLIC_ITRAJECTORYENTITY_H_