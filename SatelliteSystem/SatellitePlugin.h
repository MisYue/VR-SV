/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ������												*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SATELLITEPLUGIN_H_
#define _SATELLITEPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CSatellitePlugin :  public IPlugin
	{
	public:
		// ���캯��
		explicit CSatellitePlugin(void);
		// ��������
		virtual ~CSatellitePlugin(void);

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

#endif // !_SATELLITEPLUGIN_H_