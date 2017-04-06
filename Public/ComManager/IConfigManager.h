/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ù���ӿ�			                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ICONFIGMANAGER_H_
#define _ICONFIGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IConfigManager : public CSingleton<IConfigManager>
	{
	public:
		// ��������
		virtual ~IConfigManager() { }
		// �������
		virtual void AddConfig(IConfig* pIConfig) = 0;
		// �Ƴ�����
		virtual void RemoveConfig(IConfig* pIConfig) = 0;
	};
}

#endif // _ICONFIGMANAGER_H_