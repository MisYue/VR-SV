/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־ϵͳ����ӿ�ʵ����                                        */
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _LOGSYSTEMPLUGIN_H_
#define _LOGSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CLogSystemPlugin : public IPlugin
	{
	public:
		// ���캯��
		explicit CLogSystemPlugin(void);
		// ��������
		virtual ~CLogSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CLogSystemPlugin);
}
#endif //_LOGSYSTEMPLUGIN_H_

