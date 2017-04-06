/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体运动路径属性接口                                          */
/* 时间： 2016-06-8	                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IPATHATTRIBUTE_H_
#define _PUBLICE_IPATHATTRIBUTE_H_

namespace VR_Soft
{
	class IFeatureGeomtry;

	class VRSOFT_DLL IPath
	{
	public:
		typedef std::vector<osg::Vec3d> ListPoints;
	public:
		// 析构函数
		virtual ~IPath(void) { }
		// 获得ID
		virtual uint64_t GetID(void) const = 0;
		// 设置名称
		virtual void SetName(const VRString& strName) = 0;
		// 获得名称
		virtual VRString GetName(void) const = 0;
		// 添加一个点进入属性中
		virtual void AddKeyPoint(const osg::Vec3d& vPos) = 0;
		// 移除一个点
		virtual void RemoveKeyPoint(const int index) = 0;
		// 更改点
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos) = 0;
		// 获得某一个关键点
		virtual osg::Vec3d GetKeyPoint(int index) const = 0;
		// 获得路径关键点
		virtual const ListPoints& GetKeyPoints(void) const = 0;
		// 获得路径点
		virtual const ListPoints& GetPathPoints(void) const = 0;
		// 获得指定路径点
		virtual osg::Vec3d GetPathPoint(const int index) const = 0;
		// 设置路径策略
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey) = 0;
		// 获得路径策略
		virtual IPathStrategy* GetPathStrtegy(void) const = 0;
		// 设置渲染
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) = 0;
		// 获得渲染
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const = 0;
	};
}

#endif // !_PUBLICE_IPATHATTRIBUTE_H_