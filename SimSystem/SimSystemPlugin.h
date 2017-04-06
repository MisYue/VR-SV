/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ�����											    */
/* ʱ�䣺 2015-10-21                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SIMSYTEMPLUGIN_H_
#define _SIMSYTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CSimSystemPlugin : public IPlugin
	{
	public:
		explicit CSimSystemPlugin(void);
		virtual ~CSimSystemPlugin(void);

	public:
		// ��ȡ�������
		virtual const VRString& GetPluginName(void) const;
		// ��ò���汾
		virtual const VRString GetPluginVersion(void) const ;
		// ��ò������
		virtual const VRString& GetPluginDiscribe(void) const;
		// ��װ���
		virtual void Install(void) ;
		// ��ʼ�����
		virtual void Initialise(void);
		// ������
		virtual void Shutdown(void);
		// ж�ز��
		virtual void UnInstall(void);

	private:
		IComFactory* m_pIComFactory; // �������
	};

	// ע����
//	REGISTER_VRSOFT_PLUGIN(CSimSystemPlugin);
	REGISTER_VRSOFT_PLUGIN(CSimSystemPlugin, SIMULATION_DLL)

}

#endif // _SIMSYTEMPLUGIN_H_