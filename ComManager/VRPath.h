/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  路径关键点管理		                                        */
/* 时间： 2016-07-06                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _VRPATH_H_
#define _VRPATH_H_

#pragma once

namespace VR_Soft
{
	class CVRPath : public IPath
	{
	public:
		// 构造函数
		CVRPath(const uint64_t ID, const VRString& strName);
		// 析构函数
		virtual ~CVRPath(void);

	public:
		// 获得ID
		virtual uint64_t GetID(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName) ;
		// 获得名称
		virtual VRString GetName(void) const ;
		// 添加一个点进入属性中
		virtual void AddKeyPoint(const osg::Vec3d& vPos) ;
		// 移除一个点
		virtual void RemoveKeyPoint(const int index) ;
		// 更改点
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// 获得某一个关键点
		virtual osg::Vec3d GetKeyPoint(int index) const ;
		// 获得路径关键点
		virtual const ListPoints& GetKeyPoints(void) const;
		// 获得路径点
		virtual const ListPoints& GetPathPoints(void) const;
		// 获得指定路径点
		virtual osg::Vec3d GetPathPoint(const int index) const ;
		// 设置路径策略
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey);
		// 获得路径策略
		virtual IPathStrategy* GetPathStrtegy(void) const ;
		// 设置渲染
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) ;
		// 获得渲染
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const ;

	protected:
		// 插值计算
		void InterPolate( void );
	private:
		uint64_t m_ID;
		VRString m_strName; // 名称
		IPathStrategy* m_pIPathStrategy; // 路径策略
		IFeatureGeomtry* m_pIFeatureGeomtry; // 显示路径
		ListPoints m_listKeyPoints; // 关键点位置
		ListPoints m_listPathPoints; // 关键点位置
	};
}


#endif // !_VRPATH_H_