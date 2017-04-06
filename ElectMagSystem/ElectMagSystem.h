/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ���													*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ELECTMAGSYSTEM_H_
#define _ELECTMAGSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class IRadar;
	class CElectPluginManager;

	class CElectMagSystem : public IElecMagManager
	{
	public:
		explicit CElectMagSystem(const VRString& strName);
		virtual ~CElectMagSystem();

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��������г�ʼ��
		virtual void Init(void) ;
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void);
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		// ��ʼ��
		void InitSystem(void);

	private:
		VRString m_strName; // ����
		CElectPluginManager* m_pElectPluginManager;
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CElectMagSystem, ElecMagManager, ELECMAGSYSTEM_TYPENAME, INSTANCE_NAME_ELECMAGSYSTEM, ELECMAGSYSTEM_DISC);
}

#endif // ELECTMAGSYSTEM_H
