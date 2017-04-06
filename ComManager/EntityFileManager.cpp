#include "../../Public/VRSoft.h"
#include "EntityFileManager.h"
#include "EntityFileOperator.h"

namespace VR_Soft
{
	// ���캯��
	CEntityFileManager::CEntityFileManager(void)
	{
	}

	// ��������
	CEntityFileManager::~CEntityFileManager(void)
	{
		RemoveAll();
	}

	// �����ļ�
	void CEntityFileManager::LoadEntityFile( void )
	{
		// �Ӿ���Ŀ¼����dll��̬��
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Entity/";

		// ��ȡ��ǰĿ¼�����е��ļ�
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".xml", files);
		for(Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			// ��ѯ��ǰ�Ƿ����
			ListStrEntityFiles::const_iterator strEntityFileItor = m_listStrEntityFiles.find(*cstItor);
			if (m_listStrEntityFiles.end() != strEntityFileItor)
			{
				continue;
			}

			// ����ʵ���ļ�
			CEntityFile *pEntityFile = new CEntityFile(strCurPath + *cstItor);
			pEntityFile->Parse();
			m_listStrEntityFiles.insert(ListStrEntityFiles::value_type(pEntityFile->GetName(), pEntityFile));
		}

	}

	// ����ʵ��
	IEntityBase* CEntityFileManager::CreateEntity( const VRString& strName, const uint64_t ID )
	{
		// �����Ƿ���ڵ�ǰ��ʵ��
		ListStrEntityFiles::const_iterator cstItor = m_listStrEntityFiles.find(strName);
		if (m_listStrEntityFiles.end() == cstItor)
		{
			// ������ ���ؿ�ֵ
			return (NULL);
		}

		// ����ʵ��
		CEntityFile* entityFile = cstItor->second;
		return (entityFile->CreateEntity(strName, ID));
	}

	// ������е�ʵ������
	ListString CEntityFileManager::GetAllEntityFile( void ) const
	{
		ListString listString;
		for (ListStrEntityFiles::const_iterator cstItor = m_listStrEntityFiles.begin(); \
			m_listStrEntityFiles.end() != cstItor; ++cstItor)
		{
			listString.push_back(cstItor->first);
		}

		return (listString);
	}

	// �Ƴ����е�ʵ��
	void CEntityFileManager::RemoveAll( void )
	{
		for (ListStrEntityFiles::iterator itor = m_listStrEntityFiles.begin(); m_listStrEntityFiles.end() != itor; ++itor)
		{
			VRSOFT_DELETE(itor->second);
		}

		m_listStrEntityFiles.clear();
	}

}
