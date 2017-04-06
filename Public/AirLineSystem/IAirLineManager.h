/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IAIRLINEMANAGER_H_
#define _IAIRLINEMANAGER_H_

#pragma once

#if defined(OSGEARTH) 

#include <osgEarthSymbology/Geometry>

#define OsgEarthGeomtry osgEarth::Symbology::Geometry

#else

#define OsgEarthGeomtry void

#endif

namespace VR_Soft
{
	class ITrajectoryEntity;
	class ITrajectory;
	class IFeatureGeomtryFactory;

	const VRString AIRLINESYSTEM_TYPENAME = "AIRLINESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_AIRLINESYSTEM = "AIRLINESYSTEM";
	const VRString AIRLINESYSTEM_DISC = "����ϵͳ";

	class VRSOFT_PLUGIN_DLL IAirLineManager : public CSingleton<IAirLineManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IAirLineManager() { }

		// ��������
		virtual ITrajectoryEntity* CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) = 0;
		// �����켣�㷨
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) = 0;
		// ����������ʾ����ͼ��
		virtual IFeatureGeomtry* CreateFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry) = 0;
		// ����ͼ�γ��󹤳�
		virtual IFeatureGeomtryFactory* GetFeatureGeomtryFactory(void) const = 0;

		//// ע��༭����
		//virtual void RegisterUI(IAirLineUI* pIAirLineUI) = 0;
		//// ��ע��༭����
		//virtual void UnReginsterUI(void) = 0;
		//// ��ÿɱ༭�ĺ���
		//virtual IAirLine* GetEidtAirLine(void) const = 0;
		//// �༭���
		//virtual void EndEidtAirLine(void) = 0;
		//// ��ð󶨺���
		//virtual IAirLineBind* GetAirLineBind(void) const = 0;
	};
}


#endif //  _IAIRLINEMANAGER_H_