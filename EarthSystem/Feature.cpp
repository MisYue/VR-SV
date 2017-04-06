#include "../../Public/EarthSystem/EarthSystem.h"
#include "Feature.h"

namespace VR_Soft
{
	//----------------------------------------------------------------------------

	VRString AttributeValue::GetString() const
	{
		switch( first ) {
		case ATTRTYPE_STRING: return second.stringValue;
		case ATTRTYPE_DOUBLE: return osgEarth::toString(second.doubleValue);
		case ATTRTYPE_INT:    return osgEarth::toString(second.intValue);
		case ATTRTYPE_BOOL:   return osgEarth::toString(second.boolValue);
		case ATTRTYPE_UNSPECIFIED: break;
		}
		return "";
	}

	double	AttributeValue::GetDouble( double defaultValue ) const 
	{
		switch( first ) {
		case ATTRTYPE_STRING: return osgEarth::as<double>(second.stringValue, defaultValue);
		case ATTRTYPE_DOUBLE: return second.doubleValue;
		case ATTRTYPE_INT:    return (double)second.intValue;
		case ATTRTYPE_BOOL:   return second.boolValue? 1.0 : 0.0;
		case ATTRTYPE_UNSPECIFIED: break;
		}
		return defaultValue;
	}

	int	AttributeValue::GetInt( int defaultValue ) const 
	{
		switch( first ) {
		case ATTRTYPE_STRING: return osgEarth::as<int>(second.stringValue, defaultValue);
		case ATTRTYPE_DOUBLE: return (int)second.doubleValue;
		case ATTRTYPE_INT:    return second.intValue;
		case ATTRTYPE_BOOL:   return second.boolValue? 1 : 0;
		case ATTRTYPE_UNSPECIFIED: break;
		}
		return defaultValue;
	}

	bool AttributeValue::GetBool( bool defaultValue ) const 
	{
		switch( first ) {
		case ATTRTYPE_STRING: return osgEarth::as<bool>(second.stringValue, defaultValue);
		case ATTRTYPE_DOUBLE: return second.doubleValue != 0.0;
		case ATTRTYPE_INT:    return second.intValue != 0;
		case ATTRTYPE_BOOL:   return second.boolValue;
		case ATTRTYPE_UNSPECIFIED: break;
		}
		return defaultValue;
	}

	//----------------------------------------------------------------------------
	CFeature::CFeature(osgEarth::Features::Feature* pEarthFeature)
		:m_pFeature(pEarthFeature)
	{
	}


	CFeature::~CFeature(void)
	{
	}

	// ��õ�ǰ���Ե�ID
	unsigned long CFeature::GetFID() const
	{
		unsigned long id = 0u;
		if (m_pFeature.valid())
		{
			id = m_pFeature->getFID();
		}

		return (id);
	}

	// �������
	ListAttributeTable CFeature::GetAttributes() const
	{
		ListAttributeTable attributeTable;

		if (m_pFeature.valid())
		{
			const osgEarth::Features::AttributeTable& attrs = m_pFeature->getAttrs();
			for( osgEarth::Features::AttributeTable::const_iterator i = attrs.begin(); i != attrs.end(); ++i )
			{
				const osgEarth::Features::AttributeValue& attributeValue = i->second;
				osgEarth::Features::AttributeValueUnion avu = attributeValue.second;
				AttributeValueUnion myAvu;
				myAvu.stringValue = avu.stringValue;
				myAvu.doubleValue = avu.doubleValue;
				myAvu.intValue = avu.intValue;
				myAvu.boolValue = avu.boolValue;
				myAvu.set = avu.set;

				AttributeValue av;
				av.first = (AttributeType)attributeValue.first;
				av.second = myAvu;
				attributeTable[i->first] = av;
			}
		}
		
		return (attributeTable);
	}

	// ��������
	void CFeature::SetAttribute( const VRString& name, const VRString& value )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->set(name, value);
		}
	}

	// ��������
	void CFeature::SetAttribute( const VRString& name, double value )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->set(name, value);
		}
	}

	// ��������
	void CFeature::SetAttribute( const VRString& name, int value )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->set(name, value);
		}
	}

	// ��������
	void CFeature::SetAttribute( const VRString& name, bool value )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->set(name, value);
		}
	}

	// ��������Ϊ��
	void CFeature::SetAttributeNull( const VRString& name )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->setNull(name);
		}
	}

	// ��������Ϊ��
	void CFeature::SetAttributeNull( const VRString& name, AttributeType type )
	{
		if (m_pFeature.valid())
		{
			m_pFeature->setNull(name, (osgEarth::Features::AttributeType)type);
		}
	}

	// �ж��Ƿ��е�ǰ��ֵ
	bool CFeature::HasAttr( const VRString& name ) const
	{
		if (m_pFeature.valid())
		{
			return (m_pFeature->hasAttr(name));
		}

		return (false);
	}

	// ͨ�����Ի�������ַ���ֵ
	VRString CFeature::GetString( const VRString& name ) const
	{
		if (m_pFeature.valid())
		{
			return (m_pFeature->getString(name));
		}

		return ("");
	}

	// ͨ�����Ի������doubleֵ
	double CFeature::GetDouble( const VRString& name, double defaultValue /*=0.0 */ ) const
	{
		if (m_pFeature.valid())
		{
			return (m_pFeature->getDouble(name, defaultValue));
		}

		return (0.0);
	}

	// ͨ�����Ի������intֵ
	int CFeature::GetInt( const VRString& name, int defaultValue /*=0 */ ) const
	{
		if (m_pFeature.valid())
		{
			return (m_pFeature->getInt(name, defaultValue));
		}

		return (0);
	}

	// ͨ�����Ի������boolֵ
	bool CFeature::GetBool( const VRString& name, bool defaultValue /*=false */ ) const
	{
		if (m_pFeature.valid())
		{
			return (m_pFeature->getBool(name, defaultValue));
		}

		return (false);
	}

}

