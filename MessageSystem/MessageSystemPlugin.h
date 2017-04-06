/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��ģ����Ϣϵͳ�����                                        */
/* ʱ�䣺 2015-08-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _MESSAGESYSTEMPLUGIN_H_
#define _MESSAGESYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CMessageSystemPlugin : public IPlugin
	{
	public:
		explicit CMessageSystemPlugin(void);
		virtual ~CMessageSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CMessageSystemPlugin);
}


#endif // _MESSAGESYSTEMPLUGIN_H_