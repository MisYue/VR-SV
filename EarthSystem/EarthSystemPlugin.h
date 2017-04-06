/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ���			                                        */
/* ʱ�䣺 2015-05-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _EARTHSYSTEMPLUGIN_H_
#define _EARTHSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CEarthSystemPlugin : public IPlugin
	{
	public:
		explicit CEarthSystemPlugin(void);
		virtual ~CEarthSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CEarthSystemPlugin, OSGEARTH_DLL);
}


#endif // _EARTHSYSTEMPLUGIN_H_
