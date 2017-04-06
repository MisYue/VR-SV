/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʸ�����ݽӿ�		                                            */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		explicit CFeature(osgEarth::Features::Feature* pEarthFeature);
		// ��������
		virtual ~CFeature(void);

	public:
		// ��õ�ǰ���Ե�ID
		virtual unsigned long GetFID(void) const;
		// �������
		virtual ListAttributeTable GetAttributes() const ;
		// ��������
		virtual void SetAttribute( const VRString& name, const VRString& value ) ;
		// ��������
		virtual void SetAttribute( const VRString& name, double value ) ;
		// ��������
		virtual void SetAttribute( const VRString& name, int value ) ;
		// ��������
		virtual void SetAttribute( const VRString& name, bool value ) ;
		// ��������Ϊ��
		virtual void SetAttributeNull( const VRString& name );
		// ��������Ϊ��
		virtual void SetAttributeNull( const VRString& name, AttributeType type );
		// �ж��Ƿ��е�ǰ��ֵ
		virtual bool HasAttr( const VRString& name ) const ;
		// ͨ�����Ի�������ַ���ֵ
		virtual VRString GetString( const VRString& name ) const ;
		// ͨ�����Ի������doubleֵ
		virtual double GetDouble( const VRString& name, double defaultValue =0.0 ) const;
		// ͨ�����Ի������intֵ
		virtual int GetInt( const VRString& name, int defaultValue =0 ) const ;
		// ͨ�����Ի������boolֵ
		virtual bool GetBool( const VRString& name, bool defaultValue =false ) const ;

	private:
		osg::ref_ptr<osgEarth::Features::Feature> m_pFeature;
	};
}


#endif // !_FEATRUE_H_