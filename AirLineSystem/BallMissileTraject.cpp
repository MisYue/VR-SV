#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "BallMissileTraject.h"

#include "BallMissileTrajectEntity.h"
#include "BallMissileAttribute.h"

#include <assert.h>

namespace VR_Soft
{
	const double DTOR = osg::PI / 180.0;
	const double RTOD = (180.0/osg::PI) ;               // 弧度->度

	const double dmu = 398600.44;	        	/*地球引力常数*/
	const double dpi = 3.141592653589793238;	/*圆周率pi*/
	const double dae = 6378.145;	         	/*地球赤道半径*/
	const double dbe = 6356.76;	        		/*地球极半径*/
	const double dfe = 1/298.257;	         	/*地球扁率*/
	const double dwe = 7.2921158*0.00001;		/*地球自转角速度*/
	const double dJ2 = 1082.63e-6;            	/*地球扁率摄动系数*/
/*
	CBallMissileTraject::CBallMissileTraject(void)
		:m_pITrajectoryEntity(NULL), m_dBiasNearPoint(0.0)
	{
	}
	
	CBallMissileTraject::~CBallMissileTraject(void)
	{
	}

	// 弹道算法
	void CBallMissileTraject::AlgorithmTrajectoryPoint(void)
	{
		assert(NULL != m_pITrajectoryEntity);
		// 获取开始位置和结束位置

		// 清除数据
		m_listTrajectroryPoint.clear();

		// 获得基本属性
/*		CBallMissileAttribute* pBallmissileAttribute = m_pITrajectoryEntity->GetBallMissileAttribute();
		osg::Vec3d vStartGeoPos = pBallmissileAttribute->GetStartPoint();
		osg::Vec3d vStopGeoPos = pBallmissileAttribute->GetEndPoint();

		// 获得最高点
		double fMaxHeight = pBallmissileAttribute->GetHeight();

		// 计算中点
		osg::Vec3d vMt = (vStartGeoPos + vStopGeoPos) / 2;
		vMt.z() += fMaxHeight;
		Parabolic(vStartGeoPos, vMt, vStopGeoPos);
		return;

		// 开始时间
		double dStartTime = 0;//m_pITrajectoryEntity->GetAttribute("弹道导弹弹道属性")->GetItem("发射时间")->GetValueToDobule();

		osg::Vec3d vStartPt;
		osg::Vec3d vStopPt;

		// 转换地固坐标系
		GeoToEcf(vStartGeoPos, vStartPt);
		GeoToEcf(vStopGeoPos, vStopPt);

		// 获得中心点
		double dNormal = sqrt((vStartPt.x() + vStopPt.x())*(vStartPt.x() + vStopPt.x()) +
			(vStartPt.y() + vStopPt.y())*(vStartPt.y() + vStopPt.y()) +
			(vStartPt.z() + vStopPt.z())*(vStartPt.z() + vStopPt.z()));
		osg::Vec3d vN;
		vN.x() = (vStartPt.x() + vStopPt.x())/dNormal;
		vN.y() = (vStartPt.y() + vStopPt.y())/dNormal;
		vN.z() = (vStartPt.z() + vStopPt.z())/dNormal;

		// 计算中间点位置矢量，单位为km
		osg::Vec3d vMidPt;
		vMidPt.x() = (dae + fMaxHeight)*vN.x();
		vMidPt.y() = (dae + fMaxHeight)*vN.y();
		vMidPt.z() = (dae + fMaxHeight)*vN.z();


		// 准备工作，计算发射点与瞄准点的坐标，算法要求在地惯系下，三维直角坐标
		osg::Vec3d vStartPtECF;
		osg::Vec3d vStopPtECF;
		//张晨算法GeoToEcf计算出来有错误
		GeoToEcf(vStartGeoPos, vStartPtECF);
		GeoToEcf(vStopGeoPos, vStopPtECF);
	
		//dPresentTime:导弹相对于起始发射时间的当前时间
		double dPresentTime = 0.0;
		//计算格林威治恒星时角
		double alphaG = 0;

		// 第一步：计算轨道根数, Gibbs三矢量定轨法，计算发射点处的速度矢量
	
	
		// 根据发射点处位置矢量和速度矢量计算发射点处的轨道根数
		osg::Vec3d velocity1;
		Gibbs(vStartPt, vMidPt, vStopPt, vStartPt, velocity1);
		double orbit1[6];
		StateToOrbit(vStartPt, velocity1, orbit1);

		//根据瞄准点处位置矢量和速度矢量计算瞄准点处的轨道根数
		osg::Vec3d velocity3;
		Gibbs(vStartPt, vMidPt, vStopPt, vStopPt, velocity3);	
		double orbit3[6];
		StateToOrbit(vStopPt, velocity3, orbit3);
	


		// 第二步：计算过终点时间，见设计文档4.6.3.3.1
		double da		= orbit1[0];			//半长轴
		double de		= orbit1[1];			//偏心率
		double dIncl    = orbit1[2]*DTOR;		//轨道倾角
		double dRAAN    = orbit1[3]*DTOR;		//升交点赤经
		double dw		= orbit1[4]*DTOR;		//近地点幅角
		double dTA0      = orbit1[5]*DTOR;		//轨道根数1真近点角

		//计算过近地点时间dTimeOfPerigee，见设计文档4.6.3.3.1
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
	
		//计算轨道终止时间dStopTime
		//瞄准点轨道根数之真近点角
		double dTAf = orbit3[5]*DTOR;
		double sinEf = sqrt(1-de*de)*sin(dTAf)/(1 + de*cos(dTAf));
		double cosEf = (de + cos(dTAf))/(1 + de*cos(dTAf));
		double Ef;
		if(sinEf > 0)Ef = acos(cosEf);
		else Ef = 2*dpi - acos(cosEf);
		//过终止点时间
		double dStopTime = dTimeOfPerigee + (Ef - de*sin(Ef))/n;

		// 第三步：生成弹道点（在地惯系下）

		// 首先加入发射点（弹道的第一个点）


		//存储导弹信息，方便导弹拦截模块使用 !!!推演之前必须先加入队列
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

		// 首先加入发射点
//		pTrajectoryData->m_vTrajectoryGeo.push_back(vStartGeoPos);

		//dFlatPerigee:平近点角
		double dFlatPerigee = 0.0;
		//dTimeOfPerigee:过近地点时间

		// 获得时间步长
		double dTimeStep = 10;// m_pITrajectoryEntity->GetAttribute("弹道导弹弹道属性")->GetItem("时间步长")->GetValueToDobule();

		//计算轨道上的点数
   		int nNum =int((dStopTime- dBeginTime)/dTimeStep);
		for(int nj = 0; nj < nNum; nj++) 
		{
			TrajectoryInfo trajectoryInfo;
			//由轨道根数计算每一时刻导弹位置矢量和速度矢量
			//计算平近点角dFlatPerigee, 与真近点角可以相互转换
			osg::Vec3d vEciPt, vVelocity;
			osg::Vec3d vECFpos, vECFvel;
       		dFlatPerigee = sqrt(dmu/pow(da, 3))*(dPresentTime-dTimeOfPerigee);	
			// 计算位置和速度
			CalPosVel(orbit1, dFlatPerigee, vEciPt, vVelocity);
	
			//导弹当前位置时间进行累加
			dPresentTime = dPresentTime + dTimeStep;		// 单位为秒
			
			//当导弹位置离地心距离小于6356时，函数退出
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

			
			//计算导弹在地理坐标下的姿态角，单位为弧度	
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


			//!!!导弹信息，方便导弹拦截模块计算
			trajectoryInfo.dt = dPresentTime;
			//missileInfo.dTimeStep = dTimeStep;
			trajectoryInfo.vEcfPos = vECFpos;
			trajectoryInfo.vEciPos = vECFpos;
			vECFvel.x() = vECFvel.x() * 1e3;	//	将速度化成米每秒
			vECFvel.y() = vECFvel.y() * 1e3;
			vECFvel.z() = vECFvel.z() * 1e3;
			trajectoryInfo.vEcfVel = vECFvel;

			m_listTrajectroryPoint.push_back(trajectoryInfo);
			//pTrajectoryData->m_vMissileInfo.push_back(missileInfo);
		
		}
/*
		//最后加入瞄准点
		TrajectoryInfo endTrajectoryInfo;
		endTrajectoryInfo.vGeoPos = vStopGeoPos;
	
		//!!!导弹信息，方便导弹拦截模块计算
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

	// 设置弹道对象
	void CBallMissileTraject::SetTrajectoryEntity(IEntityBase* pITrajectoryEntity)
	{
		m_pITrajectoryEntity = dynamic_cast<CBallMissileTrajectEntity*>(pITrajectoryEntity);
	}

	// 地理坐标转地固坐标
	void CBallMissileTraject::GeoToEcf(const osg::Vec3d& vGeoPos, osg::Vec3d& vEcf)
	{
		//// 按照千米来计算
		//osg::Vec3d vGeoPosKm = vGeoPos;
		//vGeoPosKm.z() /= 1000.0;
		//CConvert::LatLongHeightToWord(vGeoPosKm, vEcf);
		//return;
		osg::Vec3d vGeoPosR;
		vGeoPosR.x() = vGeoPos.x()*DTOR;
		vGeoPosR.y() = vGeoPos.y()*DTOR;
		vGeoPosR.z() = vGeoPos.z()/1000.0;
		//地球扁率
		double dFlat = 1.0/298.257;

		double dEsqr = 2.0 * dFlat - dFlat * dFlat;

		double dN = dae / sqrt(1 - dEsqr * sin(vGeoPosR.y()))*sin(vGeoPosR.y());

		//地固坐标系下位置矢量
		vEcf.x() = (dN + vGeoPosR.z()) * cos(vGeoPosR.y()) * cos(vGeoPosR.x());
		vEcf.y() = (dN + vGeoPosR.z()) * cos(vGeoPosR.y()) * sin(vGeoPosR.x());
		vEcf.z() = (dN * (1-dEsqr) + vGeoPosR.z()) * sin(vGeoPosR.y());
	}

	//Gibbs三位置矢量定轨法，由发射点、瞄准点、中间点位置矢量计算任意其中一个点的速度矢量
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

		//求解速度矢量
		vVelo.x() = sqrt(dmu/N1/D1)*((D.y()*z - D.z()*y)/r + vS.x());   
		vVelo.y() = sqrt(dmu/N1/D1)*((D.z()*x - D.x()*z)/r + vS.y());
		vVelo.z() = sqrt(dmu/N1/D1)*((D.x()*y - D.y()*x)/r + vS.z());
	
	}

	//由位置矢量、速度矢量计算轨道根数
	void CBallMissileTraject::StateToOrbit(osg::Vec3d vPt, osg::Vec3d vVelo, double* orbit)
	{
		//1、求解轨道倾角
		osg::Vec3d h;
		h.x() = vPt.y()*vVelo.z() - vPt.z()*vVelo.y();
		h.y() = vPt.z()*vVelo.x() - vPt.x()*vVelo.z();
		h.z() = vPt.x()*vVelo.y() - vPt.y()*vVelo.x();
		double h1 = sqrt(h.x()*h.x() + h.y()*h.y() + h.z()*h.z());	
		double i = RTOD*acos(h.z()/h1);

		//2、求解升交点赤经,单位转换到度
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

		//3、求解偏心率
		osg::Vec3d e;
		double v = sqrt(vVelo.x()*vVelo.x() + vVelo.y()*vVelo.y() + vVelo.z()*vVelo.z());
		double r = sqrt(vPt.x()*vPt.x() + vPt.y()*vPt.y() + vPt.z()*vPt.z());	
		double vr = (vPt.x()*vVelo.x() + vPt.y()*vVelo.y() + vPt.z()*vVelo.z())/r;
		e.x() = 1/dmu*((v*v - dmu/r)*vPt.x() - r*vr*vVelo.x());
		e.y() = 1/dmu*((v*v - dmu/r)*vPt.y() - r*vr*vVelo.y());
		e.z() = 1/dmu*((v*v - dmu/r)*vPt.z() - r*vr*vVelo.z());
		double e1 = e.length(); // e.x()*e.x() + e.y()*e.y() + e.z()*e.z());

		//4、求解半长轴
		double a = h1*h1/dmu/(1-e1*e1);

		//5、求解近地点幅角
		double w;
		if(e.z() < 0)
		{
			w = 360 - RTOD*acos((N.x()*e.x() + N.y()*e.y() + N.z()*e.z())/N1/e1);
		}
		else
		{
			w = RTOD*acos((N.x()*e.x() + N.y()*e.y() + N.z()*e.z())/N1/e1);
		}

		//6、求解真近点角
		double f;
		if(vr < 0)
		{
			f = 360 - RTOD*acos(1/e1*(h1*h1/dmu/r - 1));
		}
		else
		{
			f = RTOD*acos(1/e1*(h1*h1/dmu/r - 1));
		}

		orbit[0] = a;		//半长轴 // LJ
		orbit[1] = e1;		//偏心率
		orbit[2] = i;		//轨道倾角
		orbit[3] = RAAN;	//升交点赤经
		orbit[4] = w;		//近地点幅角
		orbit[5] = f;		//真近点角
	}

	// 计算位置和速度
	void CBallMissileTraject::CalPosVel(double* orbit, double dFlatPerigee, osg::Vec3d& vPt, osg::Vec3d& vVelocity)
	{
		double da = orbit[0];		//半长轴
		double de = orbit[1];		//偏心率
		double dIncl = orbit[2]*DTOR;	//轨道倾角
		double dRAAN = orbit[3]*DTOR;	//升交点赤经	
		double dw = orbit[4]*DTOR;		//近地点幅角

		//dBiasPerigee偏近点角
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

	// 地惯系转地固系
	void CBallMissileTraject::EciToEcf(const osg::Vec3d& vEci, const double dLst, osg::Vec3d& vEcf)
	{
		vEcf.x() = cos(dLst)*vEci.x() + sin(dLst)*vEci.y();
		vEcf.y() = -sin(dLst)*vEci.x() + cos(dLst)*vEci.y();
		vEcf.z() = vEci.z();
	}

	void CBallMissileTraject::XYZToLBH(double X, double Y, double Z, double& L, double& B, double& H)
	{
		

		double sqrtXY2 = sqrt(X*X+Y*Y);

		//计算经度
		double dBeta = asin(fabs(Y)/sqrtXY2);  //弧度

		if(X>=0 && Y>=0) L = dBeta;            //分象限计算经度
		else if(X<0 && Y>0) L = osg::PI - dBeta;
		else if(X<0 && Y<0) L = dBeta - osg::PI;
		else if(X>0 && Y<0) L = -dBeta;

		double tanB = Z /sqrtXY2;
		B = atan(tanB);                      //弧度

		double sinB = sin(B);
		double R = 6378136.49;
		H = sqrtXY2/cos(B) - R;

		L *= RTOD;
		B *= RTOD;
	}

	// 通过抛物线拟合曲线
	void CBallMissileTraject::Parabolic( osg::Vec3d& vStart, osg::Vec3d& vMt, osg::Vec3d& vEnd )
	{
		TrajectoryInfo trajectoryInfo;
		trajectoryInfo.dt = 0;
		trajectoryInfo.vGeoPos = vStart;
		m_listTrajectroryPoint.push_back(trajectoryInfo);

		// 转换成世界坐标
		osg::Vec3d vStartWord; // 开始位置
		CConvert::LatLongHeightToWord(vStart, vStartWord);

		// 中点位置
		osg::Vec3d vMidWord; 
		CConvert::LatLongHeightToWord(vMt, vMidWord);

		// 结束点位置
		osg::Vec3d vEndWord;
		CConvert::LatLongHeightToWord(vEnd, vEndWord);

		double dStartLat = vStart.x() < 0.0 ? vStart.x() + 180.0 : vStart.x();
		double dEndLat = vEnd.x() < 0.0 ? vEnd.x() + 180.0 : vEnd.x();

		double dStartLon = vStart.y() < 0.0 ? vStart.y() + 90.0 : vStart.y();
		double dEndLon = vEnd.y() < 0.0 ? vEnd.y() + 90.0 : vEnd.y();


		// 判断哪一个抽长
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
