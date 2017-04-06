/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ù�����			                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _CONFIGMANAGER_H_
#define _CONFIGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CConfigManager : public IConfigManager
	{
	public:
		explicit CConfigManager(void);
		virtual ~CConfigManager(void);

	public:
		// �������
		virtual void AddConfig(IConfig* pIConfig);
		// �Ƴ�����
		virtual void RemoveConfig(IConfig* pIConfig);

	protected:
		typedef std::list<IConfig*> LstConfig;

	private:
		LstConfig m_lstConfig; // ���ñ�
		VR_AUTO_MUTEX
	};
}

#endif // _CONFIGMANAGER_H_
