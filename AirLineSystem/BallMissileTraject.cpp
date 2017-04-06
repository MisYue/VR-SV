#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "BallMissileTraject.h"

#include "BallMissileTrajectEntity.h"
#include "BallMissileAttribute.h"

#include <assert.h>

namespace VR_Soft
{
	const double DTOR = osg::PI / 180.0;
	const double RTOD = (180.0/osg::PI) ;               // ����->��

	const double dmu = 398600.44;	        	/*������������*/
	const double dpi = 3.141592653589793238;	/*Բ����pi*/
	const double dae = 6378.145;	         	/*�������뾶*/
	const double dbe = 6356.76;	        		/*���򼫰뾶*/
	const double dfe = 1/298.257;	         	/*�������*/
	const double dwe = 7.2921158*0.00001;		/*������ת���ٶ�*/
	const double dJ2 = 1082.63e-6;            	/*��������㶯ϵ��*/
/*
	CBallMissileTraject::CBallMissileTraject(void)
		:m_pITrajectoryEntity(NULL), m_dBiasNearPoint(0.0)
	{
	}
	
	CBallMissileTraject::~CBallMissileTraject(void)
	{
	}

	// �����㷨
	void CBallMissileTraject::AlgorithmTrajectoryPoint(void)
	{
		assert(NULL != m_pITrajectoryEntity);
		// ��ȡ��ʼλ�úͽ���λ��

		// �������
		m_listTrajectroryPoint.clear();

		// ��û�������
/*		CBallMissileAttribute* pBallmissileAttribute = m_pITrajectoryEntity->GetBallMissileAttribute();
		osg::Vec3d vStartGeoPos = pBallmissileAttribute->GetStartPoint();
		osg::Vec3d vStopGeoPos = pBallmissileAttribute->GetEndPoint();

		// �����ߵ�
		double fMaxHeight = pBallmissileAttribute->GetHeight();

		// �����е�
		osg::Vec3d vMt = (vStartGeoPos + vStopGeoPos) / 2;
		vMt.z() += fMaxHeight;
		Parabolic(vStartGeoPos, vMt, vStopGeoPos);
		return;

		// ��ʼʱ��
		double dStartTime = 0;//m_pITrajectoryEntity->GetAttribute("����������������")->GetItem("����ʱ��")->GetValueToDobule();

		osg::Vec3d vStartPt;
		osg::Vec3d vStopPt;

		// ת���ع�����ϵ
		GeoToEcf(vStartGeoPos, vStartPt);
		GeoToEcf(vStopGeoPos, vStopPt);

		// ������ĵ�
		double dNormal = sqrt((vStartPt.x() + vStopPt.x())*(vStartPt.x() + vStopPt.x()) +
			(vStartPt.y() + vStopPt.y())*(vStartPt.y() + vStopPt.y()) +
			(vStartPt.z() + vStopPt.z())*(vStartPt.z() + vStopPt.z()));
		osg::Vec3d vN;
		vN.x() = (vStartPt.x() + vStopPt.x())/dNormal;
		vN.y() = (vStartPt.y() + vStopPt.y())/dNormal;
		vN.z() = (vStartPt.z() + vStopPt.z())/dNormal;

		// �����м��λ��ʸ������λΪkm
		osg::Vec3d vMidPt;
		vMidPt.x() = (dae + fMaxHeight)*vN.x();
		vMidPt.y() = (dae + fMaxHeight)*vN.y();
		vMidPt.z() = (dae + fMaxHeight)*vN.z();


		// ׼�����������㷢�������׼������꣬�㷨Ҫ���ڵع�ϵ�£���άֱ������
		osg::Vec3d vStartPtECF;
		osg::Vec3d vStopPtECF;
		//�ų��㷨GeoToEcf��������д���
		GeoToEcf(vStartGeoPos, vStartPtECF);
		GeoToEcf(vStopGeoPos, vStopPtECF);
	
		//dPresentTime:�����������ʼ����ʱ��ĵ�ǰʱ��
		double dPresentTime = 0.0;
		//����������κ���ʱ��
		double alphaG = 0;

		// ��һ��������������, Gibbs��ʸ�����취�����㷢��㴦���ٶ�ʸ��
	
	
		// ���ݷ���㴦λ��ʸ�����ٶ�ʸ�����㷢��㴦�Ĺ������
		osg::Vec3d velocity1;
		Gibbs(vStartPt, vMidPt, vStopPt, vStartPt, velocity1);
		double orbit1[6];
		StateToOrbit(vStartPt, velocity1, orbit1);

		//������׼�㴦λ��ʸ�����ٶ�ʸ��������׼�㴦�Ĺ������
		osg::Vec3d velocity3;
		Gibbs(vStartPt, vMidPt, vStopPt, vStopPt, velocity3);	
		double orbit3[6];
		StateToOrbit(vStopPt, velocity3, orbit3);
	


		// �ڶ�����������յ�ʱ�䣬������ĵ�4.6.3.3.1
		double da		= orbit1[0];			//�볤��
		double de		= orbit1[1];			//ƫ����
		double dIncl    = orbit1[2]*DTOR;		//������
		double dRAAN    = orbit1[3]*DTOR;		//������ྭ
		double dw		= orbit1[4]*DTOR;		//���ص����
		double dTA0      = orbit1[5]*DTOR;		//�������1������

		//��������ص�ʱ��dTimeOfPerigee��������ĵ�4.6.3.3.1
		double sinE0 = sqrt(1-de*de)*sin(dTA0)/(1+de*cos(dTA0));
		double cosE0 = (de + cos(dTA0))/(1 + de*cos(dTA0));
		double n = sqrt(dmu/da/da/da);
		double dBeginTime = 0.0;
		double E0;
		if(sinE0 > 0)	
		{
			E0 = acos(cosE0);
		}
		else
		{
			E0 = 2*dpi - acos(cosE0);
		}

		double dTimeOfPerigee = dBeginTime - (E0 - de*sin(E0))/n;
	
		//��������ֹʱ��dStopTime
		//��׼��������֮������
		double dTAf = orbit3[5]*DTOR;
		double sinEf = sqrt(1-de*de)*sin(dTAf)/(1 + de*cos(dTAf));
		double cosEf = (de + cos(dTAf))/(1 + de*cos(dTAf));
		double Ef;
		if(sinEf > 0)Ef = acos(cosEf);
		else Ef = 2*dpi - acos(cosEf);
		//����ֹ��ʱ��
		double dStopTime = dTimeOfPerigee + (Ef - de*sin(Ef))/n;

		// �����������ɵ����㣨�ڵع�ϵ�£�

		// ���ȼ��뷢��㣨�����ĵ�һ���㣩


		//�洢������Ϣ�����㵼������ģ��ʹ�� !!!����֮ǰ�����ȼ������
		TrajectoryInfo trajectoryInfo;
		trajectoryInfo.dt = dPresentTime;

		osg::Vec3d vStartEcfPos;
		GeoToEcf(vStartGeoPos, vStartEcfPos);

		vStartEcfPos.x() *= 1000.0;
		vStartEcfPos.y() *= 1000.0;
		vStartEcfPos.z() *= 1000.0;
		trajectoryInfo.vEcfPos = vStartEcfPos;
		trajectoryInfo.vEciPos = vStartEcfPos;
		trajectoryInfo.vEcfVel = osg::Vec3d(0.0, 0.0, 0.0);
		trajectoryInfo.vEciVel = osg::Vec3d(0.0, 0.0, 0.0);
		trajectoryInfo.dt = dStartTime;
		trajectoryInfo.vGeoPos = vStartGeoPos;
		trajectoryInfo.vRot = osg::Vec3d(0, 0, 0);
		m_listTrajectroryPoint.push_back(trajectoryInfo);

		// ���ȼ��뷢���
//		pTrajectoryData->m_vTrajectoryGeo.push_back(vStartGeoPos);

		//dFlatPerigee:ƽ�����
		double dFlatPerigee = 0.0;
		//dTimeOfPerigee:�����ص�ʱ��

		// ���ʱ�䲽��
		double dTimeStep = 10;// m_pITrajectoryEntity->GetAttribute("����������������")->GetItem("ʱ�䲽��")->GetValueToDobule();

		//�������ϵĵ���
   		int nNum =int((dStopTime- dBeginTime)/dTimeStep);
		for(int nj = 0; nj < nNum; nj++) 
		{
			TrajectoryInfo trajectoryInfo;
			//�ɹ����������ÿһʱ�̵���λ��ʸ�����ٶ�ʸ��
			//����ƽ�����dFlatPerigee, �������ǿ����໥ת��
			osg::Vec3d vEciPt, vVelocity;
			osg::Vec3d vECFpos, vECFvel;
       		dFlatPerigee = sqrt(dmu/pow(da, 3))*(dPresentTime-dTimeOfPerigee);	
			// ����λ�ú��ٶ�
			CalPosVel(orbit1, dFlatPerigee, vEciPt, vVelocity);
	
			//������ǰλ��ʱ������ۼ�
			dPresentTime = dPresentTime + dTimeStep;		// ��λΪ��
			
			//������λ������ľ���С��6356ʱ�������˳�
			// if(sqrt(vEciPt.x()*vEciPt.x() + vEciPt.y()*vEciPt.y() + vEciPt.z()*vEciPt.z()) < 6356)
			if (vEciPt.length() < 6356)
			{
				break;
			}
			
			EciToEcf(vEciPt, alphaG, vECFpos);
			EciToEcf(vVelocity, alphaG, vECFvel);
			vECFpos.x() *= 1000.0;
			vECFpos.y() *= 1000.0;
			vECFpos.z() *= 1000.0;
			osg::Vec3d vLBHEcf;

			XYZToLBH(vECFpos.x(), vECFpos.y(), vECFpos.z(), vLBHEcf.x(), vLBHEcf.y(), vLBHEcf.z());
			//XYZToLBH(vECFpos.x, vECFpos.y, vECFpos.z, vLBHEcf.x, vLBHEcf.y, vLBHEcf.z);
			// pTrajectoryData->m_vTrajectoryGeo.push_back(vLBHEcf);
			vLBHEcf.z() *= 0.0001;

			trajectoryInfo.vGeoPos = vLBHEcf;

			
			//���㵼���ڵ��������µ���̬�ǣ���λΪ����	
			double dL = vLBHEcf.x()*DTOR;
			double dB = vLBHEcf.y()*DTOR;
			double dvrx = -sin(dL)*vVelocity.x() + cos(dL)*vVelocity.y();
			double dvry = -sin(dB)*cos(dL)*vVelocity.x() - sin(dB)*sin(dL)*vVelocity.y() + cos(dB)*vVelocity.z();
			double dvrz = cos(dB)*cos(dL)*vVelocity.x() + cos(dB)*sin(dL)*vVelocity.y() + sin(dB)*vVelocity.z();
		
			double dRotatex = osg::PI_2 - acos(dvrz/sqrt(dvrx*dvrx +dvry*dvry + dvrz*dvrz));
			double dRotatez;
			if(dvrx > 0)
			{
				dRotatez = -acos(dvry/sqrt(dvrx*dvrx + dvry*dvry));
			}
			else
			{
				dRotatez = -2*osg::PI + acos(dvry/sqrt(dvrx*dvrx + dvry*dvry));
			}
		
			osg::Vec3d vRotateAngle;
			vRotateAngle.x() = dRotatex;
			vRotateAngle.y() = dRotatex;
			vRotateAngle.z() = dRotatez;
			trajectoryInfo.vRot = vRotateAngle;
			//(pTrajectoryData->m_vAttitude).push_back(vRotateAngle);
			//////////////////////////////////////////////////////////////////////////


			//!!!������Ϣ�����㵼������ģ�����
			trajectoryInfo.dt = dPresentTime;
			//missileInfo.dTimeStep = dTimeStep;
			trajectoryInfo.vEcfPos = vECFpos;
			trajectoryInfo.vEciPos = vECFpos;
			vECFvel.x() = vECFvel.x() * 1e3;	//	���ٶȻ�����ÿ��
			vECFvel.y() = vECFvel.y() * 1e3;
			vECFvel.z() = vECFvel.z() * 1e3;
			trajectoryInfo.vEcfVel = vECFvel;

			m_listTrajectroryPoint.push_back(trajectoryInfo);
			//pTrajectoryData->m_vMissileInfo.push_back(missileInfo);
		
		}
/*
		//��������׼��
		TrajectoryInfo endTrajectoryInfo;
		endTrajectoryInfo.vGeoPos = vStopGeoPos;
	
		//!!!������Ϣ�����㵼������ģ�����
		endTrajectoryInfo.dt = dPresentTime;

		osg::Vec3d vStopEcfPos;
		GeoToEcf(vStopGeoPos, vStopEcfPos);
		vStopEcfPos.x() *= 1000.0;
		vStopEcfPos.y() *= 1000.0;
		vStopEcfPos.z() *= 1000.0;
		endTrajectoryInfo.vEcfPos = vStopEcfPos;
		endTrajectoryInfo.vEciPos = vStopEcfPos;

		endTrajectoryInfo.vEcfVel = osg::Vec3d(0.0, 0.0, 0.0);
		endTrajectoryInfo.vEciVel = osg::Vec3d(0.0, 0.0, 0.0);
		endTrajectoryInfo.vRot = osg::Vec3d(0.0, 0.0, 0.0);
		m_listTrajectroryPoint.push_back(endTrajectoryInfo);

		*/
/*	}

	// ���õ�������
	void CBallMissileTraject::SetTrajectoryEntity(IEntityBase* pITrajectoryEntity)
	{
		m_pITrajectoryEntity = dynamic_cast<CBallMissileTrajectEntity*>(pITrajectoryEntity);
	}

	// ��������ת�ع�����
	void CBallMissileTraject::GeoToEcf(const osg::Vec3d& vGeoPos, osg::Vec3d& vEcf)
	{
		//// ����ǧ��������
		//osg::Vec3d vGeoPosKm = vGeoPos;
		//vGeoPosKm.z() /= 1000.0;
		//CConvert::LatLongHeightToWord(vGeoPosKm, vEcf);
		//return;
		osg::Vec3d vGeoPosR;
		vGeoPosR.x() = vGeoPos.x()*DTOR;
		vGeoPosR.y() = vGeoPos.y()*DTOR;
		vGeoPosR.z() = vGeoPos.z()/1000.0;
		//�������
		double dFlat = 1.0/298.257;

		double dEsqr = 2.0 * dFlat - dFlat * dFlat;

		double dN = dae / sqrt(1 - dEsqr * sin(vGeoPosR.y()))*sin(vGeoPosR.y());

		//�ع�����ϵ��λ��ʸ��
		vEcf.x() = (dN + vGeoPosR.z()) * cos(vGeoPosR.y()) * cos(vGeoPosR.x());
		vEcf.y() = (dN + vGeoPosR.z()) * cos(vGeoPosR.y()) * sin(vGeoPosR.x());
		vEcf.z() = (dN * (1-dEsqr) + vGeoPosR.z()) * sin(vGeoPosR.y());
	}

	//Gibbs��λ��ʸ�����취���ɷ���㡢��׼�㡢�м��λ��ʸ��������������һ������ٶ�ʸ��
	void CBallMissileTraject::Gibbs(osg::Vec3d vStartPos, osg::Vec3d vMidPos, osg::Vec3d vStopPos, osg::Vec3d vPt, osg::Vec3d& vVelo)
	{
		double x1 = vStartPos.x();
		double y1 = vStartPos.y();
		double z1 = vStartPos.z();

		double x2 = vMidPos.x();
		double y2 = vMidPos.y();
		double z2 = vMidPos.z();

		double x3 = vStopPos.x();
		double y3 = vStopPos.y();
		double z3 = vStopPos.z();

		double x = vPt.x();
		double y = vPt.y();
		double z = vPt.z();

		double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
		double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
		double r3 = sqrt(x3*x3 + y3*y3 + z3*z3);
		double r = sqrt(x*x + y*y + z*z);

		osg::Vec3d c12;
		c12.x() = y1*z2 - y2*z1;
		c12.y() = z1*x2 - z2*x1;
		c12.z() = x1*y2 - x2*y1;

		osg::Vec3d c23;
		c23.x() = y2*z3 - y3*z2;
		c23.y() = z2*x3 - z3*x2;
		c23.z() = x2*y3 - x3*y2;

		osg::Vec3d c31;
		c31.x() = y3*z1 - y1*z3;
		c31.y() = z3*x1 - z1*x3;
		c31.z() = x3*y1 - x1*y3;

		osg::Vec3d u1;
		u1.x() = x1/r1;
		u1.y() = y1/r1;
		u1.z() = z1/r1;

		osg::Vec3d uc;
		double c = sqrt(c23.x()*c23.x() + c23.y()*c23.y() + c23.z()*c23.z());
		uc.x() = c23.x()/c;
		uc.y() = c23.y()/c;
		uc.z() = c23.z()/c;

		double flag = abs(uc.x()*u1.x() + uc.y()*u1.y() + uc.z()*u1.z());
		if(flag > 10e-6)
		{
			return;
		}

		osg::Vec3d N;
		N.x() = r1*c23.x() + r2*c31.x() + r3*c12.x();
		N.y() = r1*c23.y() + r2*c31.y() + r3*c12.y();
		N.z() = r1*c23.z() + r2*c31.z() + r3*c12.z();
		double N1 = sqrt( N.x()*N.x() + N.y()*N.y() + N.z()*N.z() );

		osg::Vec3d D;
		D.x() = c12.x() + c23.x() + c31.x();
		D.y() = c12.y() + c23.y() + c31.y();
		D.z() = c12.z() + c23.z() + c31.z();
		double D1 = sqrt(D.x()*D.x() + D.y()*D.y() + D.z()*D.z());

		osg::Vec3d vS;
		vS.x() = x1*(r2 - r3) + x2*(r3 - r1) + x3*(r1 - r2);
		vS.y() = y1*(r2 - r3) + y2*(r3 - r1) + y3*(r1 - r2);
		vS.z() = z1*(r2 - r3) + z2*(r3 - r1) + z3*(r1 - r2);
		double vS1 = sqrt(vS.x()*vS.x() + vS.y()*vS.y() + vS.z()*vS.z());

		//����ٶ�ʸ��
		vVelo.x() = sqrt(dmu/N1/D1)*((D.y()*z - D.z()*y)/r + vS.x());   
		vVelo.y() = sqrt(dmu/N1/D1)*((D.z()*x - D.x()*z)/r + vS.y());
		vVelo.z() = sqrt(dmu/N1/D1)*((D.x()*y - D.y()*x)/r + vS.z());
	
	}

	//��λ��ʸ�����ٶ�ʸ������������
	void CBallMissileTraject::StateToOrbit(osg::Vec3d vPt, osg::Vec3d vVelo, double* orbit)
	{
		//1����������
		osg::Vec3d h;
		h.x() = vPt.y()*vVelo.z() - vPt.z()*vVelo.y();
		h.y() = vPt.z()*vVelo.x() - vPt.x()*vVelo.z();
		h.z() = vPt.x()*vVelo.y() - vPt.y()*vVelo.x();
		double h1 = sqrt(h.x()*h.x() + h.y()*h.y() + h.z()*h.z());	
		double i = RTOD*acos(h.z()/h1);

		//2�����������ྭ,��λת������
		double RAAN;
		osg::Vec3d N;
		N.x() = -h.y();
		N.y() = h.x();
		N.z() = 0;
		double N1 = sqrt(N.x()*N.x() + N.y()*N.y() + N.z()*N.z());
		if(N.y() < 0) 
		{
			RAAN = 360 - RTOD*acos(N.x()/N1);
		}
		else
		{
			RAAN = RTOD*acos(N.x()/N1);
		}

		//3�����ƫ����
		osg::Vec3d e;
		double v = sqrt(vVelo.x()*vVelo.x() + vVelo.y()*vVelo.y() + vVelo.z()*vVelo.z());
		double r = sqrt(vPt.x()*vPt.x() + vPt.y()*vPt.y() + vPt.z()*vPt.z());	
		double vr = (vPt.x()*vVelo.x() + vPt.y()*vVelo.y() + vPt.z()*vVelo.z())/r;
		e.x() = 1/dmu*((v*v - dmu/r)*vPt.x() - r*vr*vVelo.x());
		e.y() = 1/dmu*((v*v - dmu/r)*vPt.y() - r*vr*vVelo.y());
		e.z() = 1/dmu*((v*v - dmu/r)*vPt.z() - r*vr*vVelo.z());
		double e1 = e.length(); // e.x()*e.x() + e.y()*e.y() + e.z()*e.z());

		//4�����볤��
		double a = h1*h1/dmu/(1-e1*e1);

		//5�������ص����
		double w;
		if(e.z() < 0)
		{
			w = 360 - RTOD*acos((N.x()*e.x() + N.y()*e.y() + N.z()*e.z())/N1/e1);
		}
		else
		{
			w = RTOD*acos((N.x()*e.x() + N.y()*e.y() + N.z()*e.z())/N1/e1);
		}

		//6�����������
		double f;
		if(vr < 0)
		{
			f = 360 - RTOD*acos(1/e1*(h1*h1/dmu/r - 1));
		}
		else
		{
			f = RTOD*acos(1/e1*(h1*h1/dmu/r - 1));
		}

		orbit[0] = a;		//�볤�� // LJ
		orbit[1] = e1;		//ƫ����
		orbit[2] = i;		//������
		orbit[3] = RAAN;	//������ྭ
		orbit[4] = w;		//���ص����
		orbit[5] = f;		//������
	}

	// ����λ�ú��ٶ�
	void CBallMissileTraject::CalPosVel(double* orbit, double dFlatPerigee, osg::Vec3d& vPt, osg::Vec3d& vVelocity)
	{
		double da = orbit[0];		//�볤��
		double de = orbit[1];		//ƫ����
		double dIncl = orbit[2]*DTOR;	//������
		double dRAAN = orbit[3]*DTOR;	//������ྭ	
		double dw = orbit[4]*DTOR;		//���ص����

		//dBiasPerigeeƫ�����
		double dBiasPerigee = dFlatPerigee + (de - pow(de,3)/8)*sin(dFlatPerigee) + 1/2*(de*de)*sin(2*dFlatPerigee) + 3/8.*pow(de,3)*sin(3*dFlatPerigee);

		while(1)
		{
			m_dBiasNearPoint = dBiasPerigee - (dBiasPerigee-de*sin(dBiasPerigee)-dFlatPerigee)/(1-de*cos(dBiasPerigee));
			if((m_dBiasNearPoint-dBiasPerigee) < 0.000000001)
			{
				dBiasPerigee = m_dBiasNearPoint;
				break;
			}
			dBiasPerigee = m_dBiasNearPoint;
		}

		double dSinIncl = sin(dIncl);
		double dCosIncl = cos(dIncl);
		double dSinRAAN = sin(dRAAN);
		double dCosRAAN = cos(dRAAN);
		double dSinW = sin(dw);
		double dCosW = cos(dw);

		double dSinTruePerigee = sqrt(1-pow(de,2))*sin(dBiasPerigee)/(1-de*cos(dBiasPerigee));
		double dCosTruePerigee = (cos(dBiasPerigee)-de)/(1-de*cos(dBiasPerigee));
		double dCosAngleDistance = dCosW*dCosTruePerigee - dSinW*dSinTruePerigee;
		double dSinAngleDistance = dSinW*dCosTruePerigee + dCosW*dSinTruePerigee;
		//////////////////////////////////////////////////////////////////////////

		double dOrbitRadius = da*(1-pow(de, 2)) / (1+de*dCosTruePerigee);
		vPt.x() = dOrbitRadius*(dCosRAAN*dCosAngleDistance-dSinRAAN*dSinAngleDistance*dCosIncl);
		vPt.y() = dOrbitRadius*(dSinRAAN*dCosAngleDistance+dCosRAAN*dSinAngleDistance*dCosIncl);
		vPt.z() = dOrbitRadius*dSinAngleDistance*dSinIncl;

		double dPositionSpeed = sqrt(dmu/da/(1-pow(de,2)));
		vVelocity.x() = -dPositionSpeed*dSinTruePerigee*(dCosW*dCosRAAN-dSinW*dSinRAAN*
			dCosIncl) + dPositionSpeed*(de+dCosTruePerigee)*(-dSinW*dCosRAAN-
			dCosW*dSinRAAN*dCosIncl);
		vVelocity.y() = -dPositionSpeed*dSinTruePerigee*(dCosW*dSinRAAN+dSinW*dCosRAAN*
			dCosIncl) +dPositionSpeed*(de+dCosTruePerigee)*(-dSinW*dSinRAAN+
			dCosW*dCosRAAN*dCosIncl);
		vVelocity.z() = -dPositionSpeed*dSinTruePerigee*(dSinW*dSinIncl) + dPositionSpeed*
			(de+dCosTruePerigee)*(dCosW*dSinIncl);
	}

	// �ع�ϵת�ع�ϵ
	void CBallMissileTraject::EciToEcf(const osg::Vec3d& vEci, const double dLst, osg::Vec3d& vEcf)
	{
		vEcf.x() = cos(dLst)*vEci.x() + sin(dLst)*vEci.y();
		vEcf.y() = -sin(dLst)*vEci.x() + cos(dLst)*vEci.y();
		vEcf.z() = vEci.z();
	}

	void CBallMissileTraject::XYZToLBH(double X, double Y, double Z, double& L, double& B, double& H)
	{
		

		double sqrtXY2 = sqrt(X*X+Y*Y);

		//���㾭��
		double dBeta = asin(fabs(Y)/sqrtXY2);  //����

		if(X>=0 && Y>=0) L = dBeta;            //�����޼��㾭��
		else if(X<0 && Y>0) L = osg::PI - dBeta;
		else if(X<0 && Y<0) L = dBeta - osg::PI;
		else if(X>0 && Y<0) L = -dBeta;

		double tanB = Z /sqrtXY2;
		B = atan(tanB);                      //����

		double sinB = sin(B);
		double R = 6378136.49;
		H = sqrtXY2/cos(B) - R;

		L *= RTOD;
		B *= RTOD;
	}

	// ͨ���������������
	void CBallMissileTraject::Parabolic( osg::Vec3d& vStart, osg::Vec3d& vMt, osg::Vec3d& vEnd )
	{
		TrajectoryInfo trajectoryInfo;
		trajectoryInfo.dt = 0;
		trajectoryInfo.vGeoPos = vStart;
		m_listTrajectroryPoint.push_back(trajectoryInfo);

		// ת������������
		osg::Vec3d vStartWord; // ��ʼλ��
		CConvert::LatLongHeightToWord(vStart, vStartWord);

		// �е�λ��
		osg::Vec3d vMidWord; 
		CConvert::LatLongHeightToWord(vMt, vMidWord);

		// ������λ��
		osg::Vec3d vEndWord;
		CConvert::LatLongHeightToWord(vEnd, vEndWord);

		double dStartLat = vStart.x() < 0.0 ? vStart.x() + 180.0 : vStart.x();
		double dEndLat = vEnd.x() < 0.0 ? vEnd.x() + 180.0 : vEnd.x();

		double dStartLon = vStart.y() < 0.0 ? vStart.y() + 90.0 : vStart.y();
		double dEndLon = vEnd.y() < 0.0 ? vEnd.y() + 90.0 : vEnd.y();


		// �ж���һ���鳤
		bool b = false;
		if((dEndLat - dStartLat) / 2.0 > dEndLon - dStartLon)
		{
			b = true;
		}
		else
		{
			b = false;
		}



		trajectoryInfo.vGeoPos = vMt;
		m_listTrajectroryPoint.push_back(trajectoryInfo);

		trajectoryInfo.vGeoPos = vEnd;
		m_listTrajectroryPoint.push_back(trajectoryInfo);

		
	}
	*/
}
