/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��������������ʵ��											*/
/* ʱ�䣺 2016-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _BALLMISSILETRAJECTENTITY_H_
#define _BALLMISSILETRAJECTENTITY_H_

#pragma once

namespace VR_Soft
{
/*	class CBallMissileAttribute;

	class CBallMissileTrajectEntity : public CEntityBaseImp<ITrajectoryLineEntity>
	{
	public:
		CBallMissileTrajectEntity(void);
		virtual ~CBallMissileTrajectEntity(void);

	public:
		// ��ʼ��
		virtual void Init(void);
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// �������
		virtual const VRString GetEntityType(void) const;

		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt);
		// �����Ⱦ��õ�����
		virtual ITrajectory* GetTrajectory(void) const;
		// ���ʵ��
		virtual void AddEntityBase( IEntityBase* pIEntityBase );
		// �Ƴ�ʵ��
		virtual void RemoveEntityBase( IEntityBase* pIEntityBase );
		// �������ʵ��
		virtual std::vector<IEntityBase* > GetAllEntity(void) const;

	public:
		// ��������
		void SetBallMissileAttribute(CBallMissileAttribute* BallMissileAttribute);
		// �������
		CBallMissileAttribute* GetBallMissileAttribute(void) const;
		// ������Ⱦ���ݵ����
		void SetTrajectory(ITrajectory* pITrajectory);
		// �Ƿ�ʼ����
		bool IsAlgorithm(void) const;
		// �Ƿ����ø���
		void SetAlgorithm(void);
		void SimRun( const CDateTime& dt );

	private:
		typedef std::vector<uint64_t> ListEntityBase;
		ListEntityBase m_listEntityBasees;

		ITrajectory* m_pITrajectory;
		CBallMissileAttribute* m_pBallMissileAttribute;
		bool m_bAlgorithm;
	};
	*/
}

#endif // !_BALLMISSILETRAJECTENTITY_H_