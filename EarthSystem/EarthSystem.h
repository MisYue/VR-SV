/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarthϵͳ����ϵͳ                                          */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _EARTHSYSTEM_H_
#define _EARTHSYSTEM_H_

#pragma once

namespace osg
{
	class Group;
}

namespace osgEarth
{
	namespace Util
	{
		class EarthManipulator;
	}
};

#include <osgEarth/Viewpoint>



namespace VR_Soft
{

	class IEarth;
	class COsgEarth;
	class CSynchroManipManager;
	class CEarthLayerManager;
	class CFeatureManager;

	class CEarthSystem : public IEarthManager
	{
	public:
		// ���캯��
		explicit CEarthSystem(const VRString& strName);
		// ��������
		virtual ~CEarthSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const ;
		// ��������г�ʼ��
		virtual void Init(void) ;
		// ��õ���
		virtual IEarth* GetEarth(EARTH_TYPE et) ;
		// ��ʼ������
		virtual void RenderEarth(const EARTH_TYPE earthType, IRenderView* pIRendView);
		// ���ģ��
		virtual void AddEntity(const IEntityBase* pIEntity);
		// �����ʾ��
		virtual void AddFeatureGeometry(const IFeatureGeomtry* pIFeatureGeomtry);
		// ���ͬ��������
		virtual ISynchroManIpManager* GetSynchroManIpManager(void) const;
		// ���ͨ��λ�þ�γ�߶�
		virtual osg::Vec3d GetLongLatHightByPoint(float x, float y, double& lat, double& lon, double& height,\
			const VRString& strViewName = "mainView");
		// ���ͼ�����
		virtual IEarthLayerManager* GetEarthLayerManager(void) const ;
		// ���ʸ������
		virtual IFeatureManager* GetEarthFeatureManager(void) const;
		// ���������߿���
		virtual void SetGraticuleState(bool bShow);
		// ��������߿���
		virtual bool GetGraticuleState(void) const ;
		// ����
		virtual double Distance(const std::vector<osg::Vec3d>& listPoints) const;
		// ���㿪��
		virtual void DistanceEnable(bool bEnable);
		// ������㹦�ܿ���
		virtual bool GetDistanceEnable(void) const;

		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		// ������Ⱦ��Ӧ����ͼ
		void SetNodeToView(const VRString& strViewName);
		// ��ʼ��2��3ά����
		void Init2D3D(void);

	protected:
		
		// ��ʼ���ӵ�
		void InitViewpoint(IConfigFile *pIConfigFile, osgEarth::Util::EarthManipulator* pMp);

	private:
		IEarth* m_pEarth; // ����ģ��
		VRString m_strName; // �������
		ViewNames m_viewNames; // ��ͼ���Ƽ���
		VRString m_strFilePath;
		
		COsgEarth* m_pOsgEarth2D;
		COsgEarth* m_pOsgEarth3D; // 
		CSynchroManipManager* m_pSynchroManipManager; // ������

		osgEarth::Viewpoint m_viewPoint;
		CEarthLayerManager* m_pEarthLayerManager; // ͼ�����
		CFeatureManager* m_pFeatureManager; // ʸ�����ݹ���
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CEarthSystem, EarthManager, EARTHSYSTEM_TYPENAME, INSTANCE_NAME_EARTHSYSTEM, EARTHSYSTEM_DISC);
}


#endif // _EARTHSYSTEM_H_