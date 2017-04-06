/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���˶�������		                                        */
/* ʱ�䣺 2016-06-8														*/
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _MOVEATTRIBUTE_H_
#define _MOVEATTRIBUTE_H_


#pragma once

namespace VR_Soft
{
	class CMoveAttribute : public CAttributeImp<IEntityMoveAttribute>
	{
	public:
		// ���캯��
		CMoveAttribute(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CMoveAttribute(void);

	public:
		// ��ʼ��
		virtual void Init(void);

	public:
		// ��ʼ����ʼ��ֵ // ��ģ�ͳ���Ŀ��λ��
		virtual void InitMove(void) ;
		// ����ʵ���ٶ�
		virtual void SetVelocity(const double vVelocity);
		// ���ʵ���ٶ�
		virtual double GetVelocity(void) const ;
		// ��������ٶ�
		virtual void SetMaxVelocity(const double vVelocity) ;
		// �������ٶ�
		virtual double GetMaxVelocity(void) const;
		// ���ü��ٶ�
		virtual void SetAcceleration(const double vAcceleration) ;
		// ��ü��ٶ�
		virtual double GetAcceleration(void) const;
		// ����Ŀ��λ��
		virtual void SetTragetPosition(const osg::Vec3d& vPos);
		// ���Ŀ��λ��
		virtual osg::Vec3d GetTragetPosition(void) const ;
		// ���õ�ǰ����λ��
		virtual void SetIndex(const int index) ;
		// ��õ�ǰ����λ��
		virtual int GetIndex(void) const ;
		// ����·��
		virtual void SetMovePath(IPath* pIPath) ;
		// ���·��
		virtual IPath* GetMovePath(void) const;
		// ����
		virtual void Update(void);
		// ����xml
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
		double m_vVelocity; // �ٶ�
		double m_dMaxVel; // ����ٶ�;
		double m_dAccel; // ���ٶ�
		int m_nIndex ; // ��ǰ����
		osg::Vec3d m_vTargetPos; // Ŀ����λ��
		osg::Vec3d  m_vLastPos; // ��һ����
		double m_dInterTime; // ��ֵʱ��


		double m_dAngle;
		double m_dTargetHeight;
		double m_dTargetLon;
		double m_dTargetLat;

		double m_dMissileHeight;
		double m_dMissilePitch;
		double m_dMissileRoll;
		double m_dMiisileAzimuth;	//����

		double m_dClimb;			//������
		int m_nSecondCount;
		int m_nAzimuthFlag;

		IPath* m_pIPath; // ·������
		double m_dLength;
		double m_dCurLenth;
	};

	class CMoveAttributeFactory : public IAttributeFactory	
	{
	public:
		CMoveAttributeFactory(void):m_strAttributeName("�˶�����") { }
		virtual ~CMoveAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CMoveAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	
}

#endif // !_MOVEATTRIBUTE_H_