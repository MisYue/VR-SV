/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦϵͳ������		                                        */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _RENDERSYSTEMPLUGIN_H_
#define _RENDERSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CRenderSystemPlugin : public IPlugin
	{
	public:
		// ���캯��
		explicit CRenderSystemPlugin(void);
		// ��������
		virtual ~CRenderSystemPlugin(void);

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

	// ע����Ⱦ���
	REGISTER_VRSOFT_PLUGIN(CRenderSystemPlugin, OSGRENDER_DLL);

}

#endif


