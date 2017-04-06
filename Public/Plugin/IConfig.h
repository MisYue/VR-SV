/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ӿ�			                                        */
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ICONFIG_H_
#define _ICONFIG_H_

#pragma once

class IConfigUI;

namespace VR_Soft
{
	class VRSOFT_DLL IConfig
	{
	public:
		// ��������
		virtual ~IConfig() {}
		// ���������ļ�
		virtual void SetConfigFile(const VRString& strfile) = 0;
		// �����ļ�
		virtual bool SaveConfigFile(void) = 0;
		// ��ȡ����
		virtual bool GetUI(void) { return (false); }
		// ע������UI
		virtual void RegisterUI(IConfigUI* pConfigUI) {m_pIConfigUI = pConfigUI;}
		// ��ע������UI
		virtual void UnRegisterUI(IConfigUI* pConfigUI) { m_pIConfigUI = NULL; }

	protected:
		// �����ļ�UI
		IConfigUI* m_pIConfigUI;
	};
};

#endif // _ICONFIG_H_