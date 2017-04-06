/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ����ϵͳ���з���ʱ��Ͷ�ģ�͵���                      */
/* ʱ�䣺 2015-10-21                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SIMSYSTEM_H_
#define _SIMSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CSimSingleThreadEngine;
	class CSimTime;

	class CSimSystem : public ISimManager
	{
	public:
		// ���캯��
		explicit CSimSystem(const VRString& strName);
		// ��������
		virtual ~CSimSystem(void);

	public:
		// �����Ƿ�Ϊ������
		virtual void SetServer(const bool bServer);
		// �����Ƿ�Ϊ������
		virtual bool IsServer(void) const { return (m_bServer); }
		// ������������
		virtual void SetCmd(const SimCmd simCmd);
		// ������Ϊһ����������ֱ�ӽ���ѭ��
		virtual void Run(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// ����̶߳���
		CSimSingleThreadEngine* GetSimThreadEngine(void) const { return (m_pSimThreadEngine); }

	protected:

	private:
		VRString m_strName;
		bool m_bServer; // �Ƿ�Ϊ������
		CSimTime* m_pSimTime;
		CSimSingleThreadEngine* m_pSimThreadEngine; // �߳�����
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CSimSystem, SimManager, SIMSYSTEM_TYPENAME, INSTANCE_NAME_SIMSYSTEM, SIMSYSTEM_DISC );

}

#endif // _SIMSYSTEM_H_
