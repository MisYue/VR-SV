/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ǹ��														*/
/* ʱ�䣺 2016-04-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SATELLITETRAJECTORY_H_
#define _SATELLITETRAJECTORY_H_

#pragma once


class SGP4;
class Tle;

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw;


	class CSatelliteTrajectory : public ITrajectory
	{
	public:
		// ���캯��
		CSatelliteTrajectory(void);
		// ��������
		virtual ~CSatelliteTrajectory(void);

	public:
		// ��õ�������
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const  { return (m_listTrajectroryPoint); }
		// �����㷨
		virtual void AlgorithmTrajectoryPoint(void);
		// ���õ�������
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity);
		// ��ȡ��ǰ��λ��
		osg::Vec3d GetCurPos(CSatalliteTrajectoryDraw* pSateliteTrjDraw, const CDateTime& dt);
		// �����Ԫʱ��
		double GetEpoh(void) const;

	protected:
		// ��ʼ��
		void InitSGP4(void);

	private:
		ITrajectory::ListTrajectoryInfo m_listTrajectroryPoint; // �켣���ݶ���
		IEntityBase* m_pITrajectoryEntity; // ����ʵ��
		Tle* m_pTle; // ���и���
		SGP4* m_pSgp4;
	};

}

#endif // !_SATELLITETRAJECTORY_H_