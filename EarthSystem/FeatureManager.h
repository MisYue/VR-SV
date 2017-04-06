/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  矢量数据管理类	                                            */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _FEATUREMANAGER_H_
#define _FEATUREMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

#include <osgEarthFeatures/Feature>

namespace VR_Soft
{
	class IFeature; 

	class CFeatureManager : public CSingleton<CFeatureManager>, public IFeatureManager
	{
	public:
		typedef boost::unordered_map<unsigned long, IFeature*> ListFeatures;
	public:
		// 构造函数
		CFeatureManager(void);
		// 析构函数
		virtual ~CFeatureManager(void);

		// 添加矢量对象
		virtual bool AddFeature(IFeature* pIFearth);
		// 移除矢量对象
		virtual void RemoveFeature(unsigned long ID);
		// 查询ID
		virtual IFeature* GetFeature(unsigned long ID) const;
		// 获得当前的选择的矢量
		virtual IFeature* GetCurFeature(void) const;

	public:
		// 设置当前的矢量数据
		virtual void SetCurFeature(IFeature* pIFeature);
		// 设置当前的矢量数据
		virtual void SetCurFeature(unsigned long ID);
		// 添加矢量
		virtual bool AddFeature(osgEarth::Features::Feature* pIFeature);

	protected:
		// 清楚数据
		void Clear(void);

	private:
		ListFeatures m_listFeatures;
		IFeature* m_pICurFeature; // 当前的矢量数据
	};
}


#endif // !_FEATUREMANAGER_H_
