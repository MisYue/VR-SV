/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染几何体工厂接口											*/
/* 时间： 2016-07-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _FEATUREGEOMTRYFACTORY_H_
#define _FEATUREGEOMTRYFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CFeatureGeomtryFactory : public IFeatureGeomtryFactory
	{
	public:
		// 构造函数
		CFeatureGeomtryFactory(void);
		// 析构函数
		virtual ~CFeatureGeomtryFactory(void);

	public:
		// 创建多边形
		virtual OsgEarthGeomtry* CreatePolygon(void);
		// 创建连续的行字符串
		virtual OsgEarthGeomtry* CreateLineString(void) ;
	};
}


#endif // !_FEATUREGEOMTRYFACTORY_H_