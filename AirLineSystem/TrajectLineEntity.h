/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ʵ��													*/
/* ʱ�䣺 2016-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _TRAJECTLINEENTITY_H_
#define _TRAJECTLINEENTITY_H_

#pragma once

namespace VR_Soft
{
	class CTrajectLine;
	class CTrajectLineAttribute;

	class CTrajectLineEntity : public CEntityBaseImp<ITrajectoryLineEntity>
	{
	public:
		explicit CTrajectLineEntity(void);
		virtual ~CTrajectLineEntity(void);

	public:
		// ��ʼ��
		virtual void Init(void);
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// �������
		virtual const VRString GetEntityType(void) const;

		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt);
		// ���ʵ���������
		virtual void AddEntityBase(IEntityBase* pIEntityBase) ;
		// �Ƴ�ʵ��
		virtual void RemoveEntityBase(IEntityBase* pIEntityBase);
		// ������е�ʵ��
		virtual std::vector<IEntityBase* > GetAllEntity(void) const ;

	public:
		// ������Ⱦ����
		void SetTrajectLineAttribute(CTrajectLineAttribute* pTrajectLineAttribute);
		void SimRun( const CDateTime& dt );
	private:
		typedef std::vector<uint64_t> ListEntityBase;
		ListEntityBase m_listEntityBasees;

		CTrajectLineAttribute* m_pTrajectLineAttribute;
	};
}


#endif // !_TRAJECTLINEENTITY_H_