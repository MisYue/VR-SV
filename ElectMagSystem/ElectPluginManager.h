/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ų������													*/
/* ʱ�䣺 2015-08-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ELECTDLLMANAGER_H_
#define _ELECTDLLMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IEntityFactoryManager;

	class CElectPluginManager : public CSingleton<CElectPluginManager> 
	{
	public:
		explicit CElectPluginManager(IEntityFactoryManager* pIEntityFactoryManager);
		virtual ~CElectPluginManager(void);

		// ���ҵ�ǰ�ļ��¼��ز��
		void LoadAllElecDll(void);

	protected:
		// ��ǰ��̬���Ƿ������
		bool IsLoaded(const VRString& strElecName);
		// ���ص���dll�ļ�
		void LoadElecDll(const VRString& strElecName);
		// ж�ص���dll�ļ�
		void UnLoadElecDll(const VRString& strElecName);
		// ж�����е�dll�ļ�

		
	protected:
		typedef std::map<VRString, CDyLib*> MapElectPlugin;

	private:
		MapElectPlugin m_mapElectPlugin; // ��ǰ���صĶ�̬��
		IEntityFactoryManager* m_pIEntityFactoryManager; // ʵ��������
	};
}

#endif // _ELECTDLLMANAGER_H_