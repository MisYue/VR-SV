/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ������		                                        */
/* ʱ�䣺 2016-08-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PLOTSYSTEMPLUGIN_H_
#define _PLOTSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CPlotSystemPlugin : public IPlugin
	{
	public:
		// ���캯��
		explicit CPlotSystemPlugin(void);
		// ��������
		virtual ~CPlotSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CPlotSystemPlugin, OSGRPLOT_DLL);
}


#endif // ! _PLOTSYSTEMPLUGIN_H_