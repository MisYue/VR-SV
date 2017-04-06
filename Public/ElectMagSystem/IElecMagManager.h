/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IELECMAGMANAGER_H_
#define _IELECMAGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IRadar;
	class IState;

	const VRString ELECMAGSYSTEM_TYPENAME = "ELECMAGSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_ELECMAGSYSTEM = "ELECMAGSYSTEM";
	const VRString ELECMAGSYSTEM_DISC = "���ϵͳ";

	class ELECTMAG_DLL IElecMagManager : public IComManagerFace
	{
	public:
		// ��������
		virtual ~IElecMagManager() { }
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) = 0;
		// ���������Ч��������
		virtual 
		// �����״�
	//	virtual IRadar* CreateEntity(IEntityBaseFactory* pEntityFactory, const VRString& strName) = 0;
	};
}


#endif //  _IELECMAGMANAGER_H_