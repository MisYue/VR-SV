/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ�����												*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SATELLITESYSTEM_H_
#define _SATELLITESYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteManager;

	class CSatelliteSystem : public ISatelliteManager
	{
	public:
		// ���캯��
		explicit CSatelliteSystem(const VRString& strName);
		// ��������
		virtual ~CSatelliteSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��������г�ʼ��
		virtual void Init(void) ;
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) ;
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// �������и���
		virtual ITle* CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2) ;
		// ��������
		virtual IEntityBase* CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) ;
		// �����켣�㷨
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) ;

	private:
		VRString m_strName; // ����
		CSatelliteManager* m_pSatelliteManager; // ���ǲ������ϵͳ
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CSatelliteSystem, SatelliteManager, SATELLITESYSTEM_TYPENAME, INSTANCE_NAME_SATELLITESYSTEM, SATELLITESYSTEM_DISC);
}


#endif // !_SATELLITESYSTEM_H_