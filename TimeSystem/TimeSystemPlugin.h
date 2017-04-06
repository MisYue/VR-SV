/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־ϵͳ�ӿ�			                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _TIMESYSTEMPLUGIN_H_
#define _TIMESYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CTimeSystemPlugin : public IPlugin
	{
	public:
		// ���캯��
		explicit CTimeSystemPlugin(void);
		// ��������
		virtual ~CTimeSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CTimeSystemPlugin);
}

#endif // _TIMESYSTEMPLUGIN_H_