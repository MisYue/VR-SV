/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ�����												*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENVIRONMENTSYSTEM_H_
#define _ENVIRONMENTSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CEnvironmentManager;

	class CEnvironmentSystem : public IEnvironmentManager
	{
	public:
		// ���캯��
		explicit CEnvironmentSystem(const VRString& strName);
		// ��������
		virtual ~CEnvironmentSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��������г�ʼ��
		virtual void Init(void) ;
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) ;
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName; // ����
		CEnvironmentManager* m_pEnvironmentManager;
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CEnvironmentSystem, EnvironmentManager, ENVIRONEMNTSYSTEM_TYPENAME, INSTANCE_NAME_ENVIRONEMNTSYSTEM, ENVIRONEMNTSYSTEM_DISC);
}


#endif // !_ENVIRONMENTSYSTEM_H_