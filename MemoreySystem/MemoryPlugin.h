/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ湲������
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _MEMORYPLUGIN_H_
#define _MEMORYPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CMemoryPlugin : public IPlugin
	{
	public:
		// ���캯��
		explicit CMemoryPlugin(void);
		// ��������
		virtual ~CMemoryPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CMemoryPlugin);
}
#endif
