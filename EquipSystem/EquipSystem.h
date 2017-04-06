/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ��ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-11-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IEQUIPMANAGER_H_
#define _IEQUIPMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEquipManager;

	class CEquipSystem : public IEquipManager
	{
	public:
		explicit CEquipSystem(const VRString& strName);
		virtual ~CEquipSystem(void);

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
		// ���װ�����
		CEquipManager* GetEquipManager(void) const;

	private:
		VRString m_strName; // ����
		CEquipManager* m_pEquitManager; // װ���������
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CEquipSystem, EquipManager, EQUIPSYSTEM_TYPENAME, INSTANCE_NAME_EQUIPSYSTEM, EQUIPSYSTEM_DISC);
}


#endif //  !_IEQUIPMANAGER_H_



