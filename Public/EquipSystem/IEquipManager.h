/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ��ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-11-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IEQUIPMANAGER_H_
#define _PUBLICE_IEQUIPMANAGER_H_

#pragma once

namespace VR_Soft
{
	const VRString EQUIPSYSTEM_TYPENAME = "EQUIPSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_EQUIPSYSTEM = "EQUIPSYSTEM";
	const VRString EQUIPSYSTEM_DISC = "װ��ϵͳ";

	class VRSOFT_PLUGIN_DLL IEquipManager : public CSingleton<IEquipManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IEquipManager() { }
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) = 0;
		// �����״�
		//	virtual IRadar* CreateEntity(IEntityBaseFactory* pEntityFactory, const VRString& strName) = 0;
	};
}


#endif //  !_PUBLICE_IEQUIPMANAGER_H_