/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʸ�����ݽӿ�		                                            */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual ~IFeature(void) { }
		// ��õ�ǰ���Ե�ID
		virtual unsigned long GetFID() const = 0;
		// �������
		virtual ListAttributeTable GetAttributes() const = 0;
		// ��������
		virtual void SetAttribute( const VRString& name, const VRString& value ) = 0;
		// ��������
		virtual void SetAttribute( const VRString& name, double value ) = 0;
		// ��������
		virtual void SetAttribute( const VRString& name, int value ) = 0;
		// ��������
		virtual void SetAttribute( const VRString& name, bool value ) = 0;
		// ��������Ϊ��
		virtual void SetAttributeNull( const VRString& name ) = 0;
		// ��������Ϊ��
		virtual void SetAttributeNull( const VRString& name, AttributeType type ) = 0;
		// �ж��Ƿ��е�ǰ��ֵ
		virtual bool HasAttr( const VRString& name ) const = 0;
		// ͨ�����Ի�������ַ���ֵ
		virtual VRString GetString( const VRString& name ) const = 0;
		// ͨ�����Ի������doubleֵ
		virtual double GetDouble( const VRString& name, double defaultValue =0.0 ) const = 0;
		// ͨ�����Ի������intֵ
		virtual int GetInt( const VRString& name, int defaultValue =0 ) const = 0;
		// ͨ�����Ի������boolֵ
		virtual bool GetBool( const VRString& name, bool defaultValue =false ) const = 0;

	};
}

#endif // !_PUBLIC_IFEARTURE_H_