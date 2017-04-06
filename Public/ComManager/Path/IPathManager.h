/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  路径管理接口头文件	                                        */
/* 时间： 2016-06-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPATHMANAGER_H_
#define _PUBLIC_IPATHMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL IPathManager : public CSingleton<IPathManager>
	{
	public:
		// 析构函数
		virtual ~IPathManager(void) { }
		// 添加路径
		virtual IPath* Create(const uint64_t uID, const VRString& strName, IFeatureGeomtry* pIFeatureGeomtry, IPathStrategy* pIPathStragey = NULL) = 0;
		// 移除路径
		virtual void Remove(const uint64_t uID) = 0;
		// 查询路径
		virtual IPath* GetPath(const uint64_t uID) const = 0;
		// 查询路径通过名称
		virtual std::vector<IPath*> GetPath(const VRString& strName) const = 0;
		// 获得所有路径
		virtual std::vector<IPath*> GetAllPath(void) const = 0;
	};
}

#endif // !_PUBLIC_IPATHMANAGER_H_