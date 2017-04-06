#ifndef _IEARTHMANAGER_H_
#define _IEARTHMANAGER_H_

#pragma once

#include <vector>

namespace VR_Soft
{
	const VRString EARTHSYSTEM_TYPENAME = "EARTHSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_EARTHSYSTEM = "EARTHSYSTEM";
	const VRString EARTHSYSTEM_DISC = "����ϵͳ";

	class ISynchroManIpManager;
	class IEarthLayerManager;
	class IFeatureManager;

	class OSGEARTH_DLL IEarthManager : public CSingleton<IEarthManager>, public IComManagerFace
	{
	public:
		enum EARTH_TYPE
		{
			EARTH_2D = 1 << 0, 
			EARTH_3D = 1 << 1,
			EARTH_2D_3D = 1 << 2
		};
	public:
		// ��������
		virtual ~IEarthManager() {}
		// ��õ���
		virtual IEarth* GetEarth(EARTH_TYPE et) = 0;
		// ��ʼ������
		virtual void RenderEarth(const EARTH_TYPE earthType, IRenderView* pIRendView) = 0;
		// ���ģ��
		virtual void AddEntity(const IEntityBase* pIEntity) = 0;
		// �����ʾ��
		virtual void AddFeatureGeometry(const IFeatureGeomtry* pIFeatureGeomtry) = 0;
		// ���ͬ��������
		virtual ISynchroManIpManager* GetSynchroManIpManager(void) const = 0;
		// ���ͨ��λ�þ�γ�߶�
		virtual osg::Vec3d GetLongLatHightByPoint(float x, float y, double& lat, double& lon, double& height,\
			const VRString& strViewName = "mainView") = 0;
		// ���ͼ�����
		virtual IEarthLayerManager* GetEarthLayerManager(void) const = 0;
		// ���ʸ������
		virtual IFeatureManager* GetEarthFeatureManager(void) const = 0;
		// ���������߿���
		virtual void SetGraticuleState(bool bShow) = 0;
		// ��������߿���
		virtual bool GetGraticuleState(void) const = 0;
		// ����
		virtual double Distance(const std::vector<osg::Vec3d>& listPoints) const = 0;
		// ���㿪��
		virtual void DistanceEnable(bool bEnable) = 0;
		// ������㹦�ܿ���
		virtual bool GetDistanceEnable(void) const = 0;
		
	public:
		typedef std::vector<VRString> ViewNames;
	};
}

#endif 