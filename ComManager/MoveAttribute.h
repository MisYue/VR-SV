/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体运动属性类		                                        */
/* 时间： 2016-06-8														*/
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _MOVEATTRIBUTE_H_
#define _MOVEATTRIBUTE_H_


#pragma once

namespace VR_Soft
{
	class CMoveAttribute : public CAttributeImp<IEntityMoveAttribute>
	{
	public:
		// 构造函数
		CMoveAttribute(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CMoveAttribute(void);

	public:
		// 初始化
		virtual void Init(void);

	public:
		// 初始化开始的值 // 将模型朝向目标位置
		virtual void InitMove(void) ;
		// 设置实体速度
		virtual void SetVelocity(const double vVelocity);
		// 获得实体速度
		virtual double GetVelocity(void) const ;
		// 设置最大速度
		virtual void SetMaxVelocity(const double vVelocity) ;
		// 获得最大速度
		virtual double GetMaxVelocity(void) const;
		// 设置加速度
		virtual void SetAcceleration(const double vAcceleration) ;
		// 获得加速度
		virtual double GetAcceleration(void) const;
		// 设置目标位置
		virtual void SetTragetPosition(const osg::Vec3d& vPos);
		// 获得目标位置
		virtual osg::Vec3d GetTragetPosition(void) const ;
		// 设置当前索引位置
		virtual void SetIndex(const int index) ;
		// 获得当前索引位置
		virtual int GetIndex(void) const ;
		// 设置路径
		virtual void SetMovePath(IPath* pIPath) ;
		// 获得路径
		virtual IPath* GetMovePath(void) const;
		// 更新
		virtual void Update(void);
		// 解析xml
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);


		double JudgeAzimuth( double dMissileAngle );
		double CalcPitch( bool bFlag, double dLon, double dLat );
		void CalcAzimuth( bool bFlag, double& dHead );
		void InterPolate(double lat1Rad, double lon1Rad, double dHeight1,
			double lat2Rad, double lon2Rad, double dHeight2,
			double t,
			double& out_latRad, double& out_lonRad, double &out_Height);
	public:
		DECLARE_PROPERTY(CMoveAttribute, double, Velocity);
		DECLARE_PROPERTY(CMoveAttribute, double, MaxVel);
		DECLARE_PROPERTY(CMoveAttribute, double, Accel);
		
	private:
		double m_vVelocity; // 速度
		double m_dMaxVel; // 最大速度;
		double m_dAccel; // 加速度
		int m_nIndex ; // 当前索引
		osg::Vec3d m_vTargetPos; // 目标点的位置
		osg::Vec3d  m_vLastPos; // 上一个点
		double m_dInterTime; // 插值时间


		double m_dAngle;
		double m_dTargetHeight;
		double m_dTargetLon;
		double m_dTargetLat;

		double m_dMissileHeight;
		double m_dMissilePitch;
		double m_dMissileRoll;
		double m_dMiisileAzimuth;	//航向

		double m_dClimb;			//爬升率
		int m_nSecondCount;
		int m_nAzimuthFlag;

		IPath* m_pIPath; // 路径对象
		double m_dLength;
		double m_dCurLenth;
	};

	class CMoveAttributeFactory : public IAttributeFactory	
	{
	public:
		CMoveAttributeFactory(void):m_strAttributeName("运动属性") { }
		virtual ~CMoveAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CMoveAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	
}

#endif // !_MOVEATTRIBUTE_H_