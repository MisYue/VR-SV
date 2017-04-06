/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ������												*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENVIRONMENT_PLUGIN_
#define _ENVIRONMENT_PLUGIN_

#pragma once

namespace VR_Soft
{
	class CEnvironmentPlugin  :  public IPlugin
	{
	public:
		explicit CEnvironmentPlugin(void);
		virtual ~CEnvironmentPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CEnvironmentPlugin)
}

#endif // !_ENVIRONMENT_PLUGIN_