/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ���			                                        */
/* ʱ�䣺 2015-08-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLINESYSTEMPLUGIN_H_
#define _AIRLINESYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CAirLineSystemPlugin : public IPlugin
	{
	public:
		explicit CAirLineSystemPlugin(void);
		virtual ~CAirLineSystemPlugin(void);

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

}


#endif