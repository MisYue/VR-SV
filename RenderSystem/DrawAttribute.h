/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ����			                                        */
/* ʱ�䣺 2015-08-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _DRAWATTRIBUTE_H_
#define _DRAWATTRIBUTE_H_

#pragma once

#include <osg/Group>

namespace VR_Soft
{
	class CDrawAttribute : public CAttributeImp<IMeshDrawAttribute>
	{
	public:
		explicit CDrawAttribute(IEntityBase* pIEntityBase, const VRString& strDrawName = "cow");
		virtual ~CDrawAttribute(void);

		// ��ʼ��
		virtual void Init();
		// ����
		virtual void Update(void);
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);
		
		// ����·��
		virtual void SetMeshPath(const VRString& strMeshPath);
		// ���·��
		virtual VRString GetMeshPath(void) ;
		// ������Ⱦ��
		virtual void SetDrawObj(DrawObj* pDrawObj);

	public:
		// ��ʼ��ͨ��xml�ڵ��ʼ��
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);
		
	public:
		// ����ʵ������
		void SetMeshName(const VRString& strMeshName);
		// ���ʵ������
		VRString GetMeshName(void) const;
		// �����Ƿ�رչ���
		void SetLightOff(bool bOff);
		// �����Ƿ�رչ���
		bool GetLightOff(void) const;

	public:
		DECLARE_PROPERTY(CDrawAttribute, VRString, MeshName);
		DECLARE_PROPERTY(CDrawAttribute, bool, Light);

	private:
		osg::Node* m_pNode;

		VRString m_strMeshName;
		bool m_bLight;
		//osg::Group* m_pGroup;
	};


	class CMeshAttributeFactory : public IAttributeFactory	
	{
	public:
		CMeshAttributeFactory(void):m_strAttributeName("��άģ������") { }
		virtual ~CMeshAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CDrawAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	

}

#endif