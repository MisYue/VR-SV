/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染几何体工厂接口											*/
/* 时间： 2016-07-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IFEATUREGEOMTRYFACTORY_H_
#define _PUBLIC_IFEATUREGEOMTRYFACTORY_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IFeatureGeomtryFactory
	{
	public:
		// 析构函数
		virtual ~IFeatureGeomtryFactory(void) { }
		// 创建多边形
		virtual OsgEarthGeomtry* CreatePolygon(void) = 0;
		// 创建连续的行字符串
		virtual OsgEarthGeomtry* CreateLineString(void) = 0;
	};
}

#endif // !_PUBLIC_IFEATUREGEOMTRYFACTORY_H_