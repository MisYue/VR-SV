/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ʵ��														*/
/* ʱ�䣺 2016-04-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SATELLITEENTITY_H_
#define _SATELLITEENTITY_H_

#pragma once

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw;

	class CSatelliteEntity  : public CEntityBaseImp<ISatelliteEntity>
	{
	public:
		// ���캯��
		CSatelliteEntity(void);
		// ��������
		virtual ~CSatelliteEntity(void);

	public:
		// ��ʼ��
		virtual void Init(void);
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// �������
		virtual const VRString GetEntityType(void) const;

		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt);

	public:
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;
		// ����㷨����
		virtual ITrajectory* GetTrajectory(void);
		// ���ɹ��
		virtual void GenerateTrajectory(void) ;
		// �������и���
		virtual void SetTle(ITle* pITle) ;
		// ������и���
		virtual ITle* GetTle(void) const;

	private:
		ITrajectory* m_pITrajecoty; // �㷨����
		ITle* m_pITile; // �������

		CSatalliteTrajectoryDraw* m_pTrajectoryDrawAttribute;
	};
}


#endif // !_SATELLITEENTITY_H_