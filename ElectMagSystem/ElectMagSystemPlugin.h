/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ������												*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ELECMAGSYSTEMPLUGIN_H_
#define _ELECMAGSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class ELECTMAG_DLL CElectMagSystemPlugin : public IPlugin
	{
	public:
		explicit CElectMagSystemPlugin(void);
		virtual ~CElectMagSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CElectMagSystemPlugin, ELECTMAG_DLL);
}

#endif // _ELECMAGSYSTEMPLUGIN_H_