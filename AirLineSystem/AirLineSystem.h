/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ���													*/
/* ʱ�䣺 2015-08-03                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLINESYSTEM_H_
#define _AIRLINESYSTEM_H_

// #include "airlinesystem_global.h"

#pragma once

namespace VR_Soft
{
	class CAirLineManager;
	class CFeatureGeomtryFactory;

	class CAirLineSystem : public IAirLineManager
	{
	public:
		explicit CAirLineSystem(const VRString& strName);
		virtual ~CAirLineSystem(void);

	public:
		// ��������
		virtual ITrajectoryEntity* CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) ;
		//// �������ǹ��
		//virtual ITrajectoryEntity* CreateSatelliteTrajectory(const VRString& strName, const uint64_t ID);
		// �����켣�㷨
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) ;
		// ����������ʾ����ͼ��
		virtual IFeatureGeomtry* CreateFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry) ;
		// ����ͼ�γ��󹤳�
		virtual IFeatureGeomtryFactory* GetFeatureGeomtryFactory(void) const ;
		//// ע��༭����
		//virtual void RegisterUI(IAirLineUI* pIAirLineUI);
		//// ��ע��༭����
		//virtual void UnReginsterUI(void);
		//// ��ÿɱ༭�ĺ���
		//virtual IAirLine* GetEidtAirLine(void) const;
		//// �༭���
		//virtual void EndEidtAirLine(void) ;
		//// ��ð󶨺���
		//IAirLineBind* GetAirLineBind(void) const;

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��������г�ʼ��
		virtual void Init(void) ;
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	public:
	

	protected:
		void InitSystem(void);

	private:
		VRString m_strName; // ����
		CAirLineManager* m_pAirLineManager; // װ���������
		CFeatureGeomtryFactory* m_featureGeomtryFactory;
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CAirLineSystem, AirLineManager, AIRLINESYSTEM_TYPENAME, INSTANCE_NAME_AIRLINESYSTEM, AIRLINESYSTEM_DISC);
}

#endif // _AIRLINESYSTEM_H_
