/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  矢量数据接口		                                            */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IFEARTURE_H_
#define _PUBLIC_IFEARTURE_H_

#include <map>
#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	struct AttributeValueUnion
	{
		VRString stringValue;
		double      doubleValue;
		int         intValue;
		bool        boolValue;

		//Whether the value is set.  A value of false means the value is effectively NULL
		bool        set;
	};

	enum AttributeType
	{
		ATTRTYPE_UNSPECIFIED,
		ATTRTYPE_STRING,
		ATTRTYPE_INT,
		ATTRTYPE_DOUBLE,
		ATTRTYPE_BOOL
	};

	struct OSGEARTH_DLL AttributeValue : public std::pair<AttributeType,AttributeValueUnion>
	{    
		VRString GetString() const;
		double GetDouble( double defaultValue =0.0 ) const;
		int GetInt( int defaultValue =0 ) const;
		bool GetBool( bool defaultValue =false ) const;              
	};

	typedef boost::unordered_map<VRString, AttributeValue> ListAttributeTable;

	class OSGEARTH_DLL IFeature
	{
	public:
		// 析构函数
		virtual ~IFeature(void) { }
		// 获得当前属性的ID
		virtual unsigned long GetFID() const = 0;
		// 获得属性
		virtual ListAttributeTable GetAttributes() const = 0;
		// 设置属性
		virtual void SetAttribute( const VRString& name, const VRString& value ) = 0;
		// 设置属性
		virtual void SetAttribute( const VRString& name, double value ) = 0;
		// 设置属性
		virtual void SetAttribute( const VRString& name, int value ) = 0;
		// 设置属性
		virtual void SetAttribute( const VRString& name, bool value ) = 0;
		// 设置属性为空
		virtual void SetAttributeNull( const VRString& name ) = 0;
		// 设置属性为空
		virtual void SetAttributeNull( const VRString& name, AttributeType type ) = 0;
		// 判断是否含有当前的值
		virtual bool HasAttr( const VRString& name ) const = 0;
		// 通过属性获得属性字符串值
		virtual VRString GetString( const VRString& name ) const = 0;
		// 通过属性获得属性double值
		virtual double GetDouble( const VRString& name, double defaultValue =0.0 ) const = 0;
		// 通过属性获得属性int值
		virtual int GetInt( const VRString& name, int defaultValue =0 ) const = 0;
		// 通过属性获得属性bool值
		virtual bool GetBool( const VRString& name, bool defaultValue =false ) const = 0;

	};
}

#endif // !_PUBLIC_IFEARTURE_H_