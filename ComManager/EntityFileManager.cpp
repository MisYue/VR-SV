#include "../../Public/VRSoft.h"
#include "EntityFileManager.h"
#include "EntityFileOperator.h"

namespace VR_Soft
{
	// 构造函数
	CEntityFileManager::CEntityFileManager(void)
	{
	}

	// 析构函数
	CEntityFileManager::~CEntityFileManager(void)
	{
		RemoveAll();
	}

	// 导入文件
	void CEntityFileManager::LoadEntityFile( void )
	{
		// 从具体目录加载dll动态库
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Entity/";

		// 获取当前目录下所有的文件
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".xml", files);
		for(Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			// 查询当前是否存在
			ListStrEntityFiles::const_iterator strEntityFileItor = m_listStrEntityFiles.find(*cstItor);
			if (m_listStrEntityFiles.end() != strEntityFileItor)
			{
				continue;
			}

			// 创建实体文件
			CEntityFile *pEntityFile = new CEntityFile(strCurPath + *cstItor);
			pEntityFile->Parse();
			m_listStrEntityFiles.insert(ListStrEntityFiles::value_type(pEntityFile->GetName(), pEntityFile));
		}

	}

	// 创建实体
	IEntityBase* CEntityFileManager::CreateEntity( const VRString& strName, const uint64_t ID )
	{
		// 查找是否存在当前的实体
		ListStrEntityFiles::const_iterator cstItor = m_listStrEntityFiles.find(strName);
		if (m_listStrEntityFiles.end() == cstItor)
		{
			// 不存在 返回空值
			return (NULL);
		}

		// 创建实体
		CEntityFile* entityFile = cstItor->second;
		return (entityFile->CreateEntity(strName, ID));
	}

	// 获得所有的实体名称
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

	// 移除所有的实体
	void CEntityFileManager::RemoveAll( void )
	{
		for (ListStrEntityFiles::iterator itor = m_listStrEntityFiles.begin(); m_listStrEntityFiles.end() != itor; ++itor)
		{
			VRSOFT_DELETE(itor->second);
		}

		m_listStrEntityFiles.clear();
	}

}
