/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����������		                                        */
/* ʱ�䣺 2016-03-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _BASEATTRIBUTE_H_
#define _BASEATTRIBUTE_H_

#pragma once

namespace VR_Soft
{

	class CEntityBaseAttribute : public CAttributeImp<IEntityBaseAttribute>
	{
	public:
		// ���캯��
		explicit CEntityBaseAttribute(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CEntityBaseAttribute(void);

	public:
		// ��ʼ��
		virtual void Init();
		// ����ʵ������
		virtual void SetEntityName(const VRString& strName);
		// ���ʵ������
		virtual VRString GetEntityName(void) const;
		// ����ID�� �ڲ�����
		virtual void SetEntityID(IEntityID* pEntityID);
		// ����ID��
		virtual void SetEntityID(const uint64_t uid);
		// ���ID��
		virtual uint64_t GetEntityID(void) const;
		// ��������ϵ
		virtual void SetEntityCoordinate(const EntityCoordinate ec) ;
		// �������ϵ
		virtual EntityCoordinate GetEntityCoordinate(void) const ;
		// ��������
		virtual void SetEntityType(const VRString& strType );
		// �������
		virtual VRString GetEntityType(void) const ;

	public:
		// ��ʼ��ͨ��xml�ڵ��ʼ��
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);

	public:
		// ����
		//AutoProperty(osg::Vec3d, Postion);
		DECLARE_PROPERTY(CEntityBaseAttribute, uint64_t, ID);
		DECLARE_PROPERTY(CEntityBaseAttribute, EntityCoordinate, EntityCoordinate);
		DECLARE_PROPERTY(CEntityBaseAttribute, VRString, Name);
		DECLARE_PROPERTY(CEntityBaseAttribute, VRString, Type);
		//property<CEntityBaseAttribute, osg::Vec3d>

	private: 
		//IEntityID* m_pIEntityID; // ģ�ͱ�־ �ڴ���Ψһ��־����
		uint64_t m_uID;
		VRString m_strEntityName;
		EntityCoordinate m_entityCoordinate; // �Ƿ���������
		VRString m_strType; // ����
	};

}


#endif // _BASEATTRIBUTE_H_