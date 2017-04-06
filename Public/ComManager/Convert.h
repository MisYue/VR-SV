/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  转换工具类			                                        */
/* 时间： 2015-05-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _CONVERT_H_
#define _CONVERT_H_

#pragma once

namespace osg
{
	class Vec3d;
}
namespace osgEarth
{
	class SpatialReference;
}

namespace VR_Soft
{
	class IAttributeItem;

	const double WGS_84_RADIUS_EQUATOR = 6378137.0;
	const double WGS_84_RADIUS_POLAR = 6356752.3142;

	class VRSOFT_DLL CConvert
	{
	public:
		// 经纬高度转换成世界坐标
		static void LatLongHeightToWord(const double latitude, const double longitude, const double height, \
			double& X, double& Y, double& Z) ;
		// 经纬高度转换成世界坐标
		static void LatLongHeightToWord(const osg::Vec3d& vGeo, osg::Vec3d& vWord);
		// 世界坐标转换成地理坐标
		static void WordToLatLongHeight(const osg::Vec3d& vWord, osg::Vec3d& vGeo);
		// 世界坐标转换成地理坐标
		static void WordToLatLongHeight(const double X, const double Y, const double Z, \
			double& latitude, double& longitude, double& height) ;

		template <class T>
		static bool CanvartType(const IAttributeItem* pAttributeItem, T& var);
	public:
		static osgEarth::SpatialReference* m_pSpatial;

	private:
		//  不允许等于 构造拷贝 判断是否相等 赋值 并且不能有初始化对象派生等默认c++操作
		explicit CConvert(void);
		CConvert(const CConvert& other);
		CConvert operator= (const CConvert& other);
		bool operator== (const CConvert& other);
		bool operator!= (const CConvert& other);



	};
}


#endif // _CONVERT_H_