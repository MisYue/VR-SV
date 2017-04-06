/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  矢量数据接口		                                            */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _FEATRUE_H_
#define _FEATRUE_H_

#pragma once

#include <osgEarthFeatures/Feature>

namespace VR_Soft
{
	class CFeature : public IFeature
	{
	public:
		// 构造函数
		explicit CFeature(osgEarth::Features::Feature* pEarthFeature);
		// 析构函数
		virtual ~CFeature(void);

	public:
		// 获得当前属性的ID
		virtual unsigned long GetFID(void) const;
		// 获得属性
		virtual ListAttributeTable GetAttributes() const ;
		// 设置属性
		virtual void SetAttribute( const VRString& name, const VRString& value ) ;
		// 设置属性
		virtual void SetAttribute( const VRString& name, double value ) ;
		// 设置属性
		virtual void SetAttribute( const VRString& name, int value ) ;
		// 设置属性
		virtual void SetAttribute( const VRString& name, bool value ) ;
		// 设置属性为空
		virtual void SetAttributeNull( const VRString& name );
		// 设置属性为空
		virtual void SetAttributeNull( const VRString& name, AttributeType type );
		// 判断是否含有当前的值
		virtual bool HasAttr( const VRString& name ) const ;
		// 通过属性获得属性字符串值
		virtual VRString GetString( const VRString& name ) const ;
		// 通过属性获得属性double值
		virtual double GetDouble( const VRString& name, double defaultValue =0.0 ) const;
		// 通过属性获得属性int值
		virtual int GetInt( const VRString& name, int defaultValue =0 ) const ;
		// 通过属性获得属性bool值
		virtual bool GetBool( const VRString& name, bool defaultValue =false ) const ;

	private:
		osg::ref_ptr<osgEarth::Features::Feature> m_pFeature;
	};
}


#endif // !_FEATRUE_H_