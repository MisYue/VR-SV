/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���ļ�����������	                                        */
/* ʱ�䣺 2016-06-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYFILEMANAGER_H_
#define _ENTITYFILEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEntityFile;

	class CEntityFileManager : public CSingleton<CEntityFileManager>
	{
	public:
		// ���캯��
		CEntityFileManager(void);
		// ��������
		~CEntityFileManager(void);

	public:
		// �����ļ�
		void LoadEntityFile(void);
		// ����ʵ��
		IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID);
		// ������е�ʵ������
		ListString GetAllEntityFile(void) const;

	protected:
		// �Ƴ����е�ʵ��
		void RemoveAll(void);

	protected:
		typedef boost::unordered_map<VRString, CEntityFile*> ListStrEntityFiles;
	private:
		ListStrEntityFiles m_listStrEntityFiles;
	};
}


#endif // !_ENTITYFILEMANAGER_H_