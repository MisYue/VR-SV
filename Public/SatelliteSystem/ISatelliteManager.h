/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISATELLITEMANAGER_H_
#define _PUBLICE_ISATELLITEMANAGER_H_

namespace VR_Soft
{
	const VRString SATELLITESYSTEM_TYPENAME = "SATELLITESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_SATELLITESYSTEM = "SATELLITESYSTEM";
	const VRString SATELLITESYSTEM_DISC = "����ϵͳ";

	class ITle;

	class VRSOFT_PLUGIN_DLL ISatelliteManager : public CSingleton<ISatelliteManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~ISatelliteManager(void) { }
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) = 0;
		// �������и���
		virtual ITle* CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2) = 0;
		// ��������
		virtual IEntityBase* CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) = 0;
		// �����켣�㷨
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) = 0;
	};
}

#endif