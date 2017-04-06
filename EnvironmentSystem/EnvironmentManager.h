/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ģ�͹���													*/
/* ʱ�䣺 2015-11-24                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENRIRONMENTMANAGER_H_
#define _ENRIRONMENTMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEnvironmentManager
	{
	public:
		CEnvironmentManager(IEntityFactoryManager* pIEntityFactoryManager);
		~CEnvironmentManager(void);

		void LoadAllElecDll(void);

	protected:
		// ��ǰ��̬���Ƿ������
		bool IsLoaded(const VRString& strElecName);
		// ���ص���dll�ļ�
		void LoadElecDll(const VRString& strElecName);
		// ж�ص���dll�ļ�
		void UnLoadElecDll(const VRString& strElecName);

	protected:
		typedef std::map<VRString, CDyLib*> ListEnvironPlugin;

	private:
		ListEnvironPlugin m_lstEnvironPlugins; // ����
		IEntityFactoryManager* m_pIEntityFactoryManager; // ʵ�幤���������
	};
}


#endif // !_ENRIRONMENTMANAGER_H_