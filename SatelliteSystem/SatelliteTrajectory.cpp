#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteTrajectory.h"
#include "SatelliteEntity.h"
#include "SatelliteTrajectoryDraw.h"

//#include "Norad/cTLE.h"
//#include "Norad/cEci.h"
//#include "Norad/cOrbit.h"
//#include "Norad/cSite.h"

#include "Sgp4lib/SGP4.h"
#include "Sgp4lib/DateTime.h"

namespace VR_Soft
{
	CSatelliteTrajectory::CSatelliteTrajectory(void)
		:m_pTle(NULL), m_pSgp4(NULL)
	{
	}


	CSatelliteTrajectory::~CSatelliteTrajectory(void)
	{
		VRSOFT_DELETE(m_pTle);
		VRSOFT_DELETE(m_pSgp4);
	}

	// �����㷨
	void CSatelliteTrajectory::AlgorithmTrajectoryPoint(void)
	{
		InitSGP4();

		CDateTime dtSim = ISimManager::GetInstance().GetStartTime();
		DateTime dt(dtSim.GetTicks());
	/*	double dSimStartTime = dt.ToJulian();
		double dStartTime = (dSimStartTime - m_dEpoh) * 1440;*/

		// ���һ�ܵ�ʱ��
		double dCye = m_pTle->MeanMotion();
		double d = 1 / dCye * 86400;
		int nCount = (int)d;

		for (int mpe = 0; mpe <= nCount; mpe += 1)
		{
			// Get the position of the satellite at time "mpe"
			// The coordinates are placed into the local variable "eci".
			//double dt = dStartTime + mpe;
			DateTime dateTime = dt.AddSeconds(mpe);
			Eci eci = m_pSgp4->FindPosition( dateTime); // sgp4.FindPosition(dt);

			// ת���ع�ϵ����ϵ
			CoordGeodetic geoPos = eci.ToGeodetic();
		/*	orbit.getPosition(dt, &eci);
			mTest = eci.toGeo();*/


			TrajectoryInfo trajectoryInfo;
			trajectoryInfo.dt = dateTime.ToJulian(); // dSimStartTime + mpe;
			osg::Vec3d vGeoPos = osg::Vec3d(osg::RadiansToDegrees(geoPos.longitude), osg::RadiansToDegrees(geoPos.latitude), geoPos.altitude * 1000 ); // �����ת���ɵع�ϵ����
			trajectoryInfo.vGeoPos = vGeoPos;

			// ת������������
			osg::Vec3d vWorld = osg::Vec3d(eci.Position().x, eci.Position().y, eci.Position().z) * 1000; // ��������������
			// CConvert::LatLongHeightToWord(vGeoPos,vWorld);
			trajectoryInfo.vEcfPos = vWorld; // osg::Vec3d(eci.getPos().m_x, eci.getPos().m_y, eci.getPos().m_z);
			trajectoryInfo.vEciPos = vWorld; // osg::Vec3d(eci.getPos().m_x, eci.getPos().m_y, eci.getPos().m_z);
			trajectoryInfo.vEcfVel = osg::Vec3d(eci.Velocity().x, eci.Velocity().y, eci.Velocity().z);
			trajectoryInfo.vRot = osg::Vec3d(0, 0, 0);
			m_listTrajectroryPoint.push_back(trajectoryInfo);
		}

	}

	// ���õ�������
	void CSatelliteTrajectory::SetTrajectoryEntity(IEntityBase* pITrajectoryEntity)
	{
		m_pITrajectoryEntity = pITrajectoryEntity;
		
	}

	// ��ȡ��ǰ��λ��
	osg::Vec3d CSatelliteTrajectory::GetCurPos(CSatalliteTrajectoryDraw* pSateliteTrjDraw, const CDateTime& dt)
	{
		// double dSimTimer = (dt - m_dEpoh) * 1440;
		int nSize = (int)m_listTrajectroryPoint.size();

		double dJulian = dt.GetJulian();

		int nPos = 0;
		double dTime = 0.0;
		for (int index = 0; index < nSize; ++index)
		{
			dTime = m_listTrajectroryPoint[index].dt;
			if (dJulian < dTime)
			{
				nPos = index;
				// ת����Ⱦ��
				break;
			}
		}

		// �ж��Ƿ��Ѿ����·��
		if (nPos >= nSize)
		{
			return (m_listTrajectroryPoint[nPos - 1].vGeoPos);
		}

		
	//	double d = dt.ToJulian();

		// ��������ת
		pSateliteTrjDraw->UpdateMatrix(dJulian);

		// λ�����ƽ��
		int nNextPos = (nPos + 1) >= nSize ? nSize - 1 : nPos + 1;
		const TrajectoryInfo v = m_listTrajectroryPoint[nPos];
		const TrajectoryInfo vSec = m_listTrajectroryPoint[nNextPos];
		double delta_time = vSec.dt - v.dt;
		double ratio = (dJulian - v.dt) / delta_time;
		double one_minus_ratio = 1.0-ratio;
		osg::Vec3 vPos(v.vGeoPos * one_minus_ratio + vSec.vGeoPos * ratio);

		return (vPos);
// 
// 		return (m_listTrajectroryPoint[nPos].vGeoPos); // ������������ֵ
	}

	// �����Ԫʱ��
	double CSatelliteTrajectory::GetEpoh(void) const
	{
		return (NULL == m_pTle ? 0.0 : m_pTle->Epoch().ToJulian() );
	}

	void CSatelliteTrajectory::InitSGP4(void)
	{
		if (NULL != m_pSgp4)
		{
			return;
		}

		CSatelliteEntity* pSatelliteEntity = dynamic_cast<CSatelliteEntity*>(m_pITrajectoryEntity);

		// ��ʼ��
		ITle* pITle = pSatelliteEntity->GetTle();
		m_pTle = new Tle(pITle->GetName(), pITle->GetLine1(), pITle->GetLine2());
		m_pSgp4 = new SGP4(*m_pTle);
	}

}
