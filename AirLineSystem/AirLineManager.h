/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ���������													*/
/* ʱ�䣺 2015-08-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _AIRLINEMANAGER_H_
#define _AIRLINEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CAirLineManager
	{
	public:
		explicit CAirLineManager(IEntityFactoryManager* pIEntityFactoryManager);
		virtual ~CAirLineManager(void);

		// ���ҵ�ǰ�ļ��¼��ز��
		void LoadAllElecDll(void);

	protected:
		// ��ǰ��̬���Ƿ������
		bool IsLoaded(const VRString& strElecName);
		// ���ص���dll�ļ�
		void LoadElecDll(const VRString& strElecName);
		// ж�ص���dll�ļ�
		void UnLoadElecDll(const VRString& strElecName);

	protected:
		typedef std::map<VRString, CDyLib*> ListEquipPlugin;

	private:
		ListEquipPlugin m_lstEquipPlugin; // װ��
		IEntityFactoryManager* m_pIEntityFactoryManager; // ʵ�幤���������
	};
}


#endif // !_AIRLINEMANAGER_H_