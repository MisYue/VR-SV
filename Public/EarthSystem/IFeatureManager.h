/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  矢量数据管理类接口                                            */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_FEATUREMANAGER_H_
#define _PUBLIC_FEATUREMANAGER_H_

namespace VR_Soft
{
	class IFeatureManager 
	{
	public:
		// 析构函数
		virtual ~IFeatureManager(void) { }

		// 添加矢量对象
		virtual bool AddFeature(IFeature* pIFearth) = 0;
		// 移除矢量对象
		virtual void RemoveFeature(unsigned long ID) = 0;
		// 查询ID
		virtual IFeature* GetFeature(unsigned long ID) const = 0;
		// 获得当前的选择的矢量
		virtual IFeature* GetCurFeature(void) const = 0;
	};
}

#endif // !_PUBLIC_FEATUREMANAGER_H_