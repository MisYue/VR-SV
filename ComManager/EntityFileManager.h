/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体文件操作管理类	                                        */
/* 时间： 2016-06-18                                                    */
/* 修改时间:                                                            */
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
		// 构造函数
		CEntityFileManager(void);
		// 析构函数
		~CEntityFileManager(void);

	public:
		// 导入文件
		void LoadEntityFile(void);
		// 创建实体
		IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID);
		// 获得所有的实体名称
		ListString GetAllEntityFile(void) const;

	protected:
		// 移除所有的实体
		void RemoveAll(void);

	protected:
		typedef boost::unordered_map<VRString, CEntityFile*> ListStrEntityFiles;
	private:
		ListStrEntityFiles m_listStrEntityFiles;
	};
}


#endif // !_ENTITYFILEMANAGER_H_