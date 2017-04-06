/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ���Խӿ���	                                        */
/* ʱ�䣺 2016-08-10                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYDRAWATTRIUBTE_H_
#define _ENTITYDRAWATTRIUBTE_H_

#pragma once

namespace VR_Soft
{
	class CEntityDrawAttribute : public CAttributeImp<IEntityDrawAttribute>
	{
	public:
		// ���캯��
		explicit CEntityDrawAttribute(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CEntityDrawAttribute(void);

	public:
		// ��ʼ��
		virtual void Init();
		// ���λ��
		virtual void SetPosition(const osg::Vec3d& vPos) ;
		// ���λ��
		virtual osg::Vec3d GetPosition(void) const ;
		// ��������
		virtual void SetScale(const osg::Vec3d& vScale) ;
		// �������
		virtual osg::Vec3d GetScale(void) const ;
		// ������ת
		virtual void SetRotate(const osg::Vec3d& vRot);
		// �����ת
		virtual osg::Vec3d GetRotate(void) const ;
		// ������ʾģʽ
		virtual void SetDrawModel(const DrawModel dm);
		// �����ʾģʽ
		virtual DrawModel GetDrawModel(void) const;
		// ���ö�ά��ʾͼƬ
		virtual void SetEntity2D(const VRString& strFile);
		// ��ö�ά��ʾͼƬ
		virtual VRString GetEntity2D(void) const;
		// �Ƿ�ı䵱ǰ�Ķ�άͼƬ
		virtual bool ChangeEntity2D(void) const;

	public:
		// ��ʼ��ͨ��xml�ڵ��ʼ��
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);

	public:
		// ����
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Position);
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Scale);
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Rotate);
		DECLARE_PROPERTY(CEntityDrawAttribute, DrawModel, DrawModel);
		DECLARE_PROPERTY(CEntityDrawAttribute, VRString, Entity2D);

	private:
		osg::Vec3d m_vPostion; // λ��
		osg::Vec3d m_vScale; // ����
		osg::Vec3d m_vRotate; // ��ת
		DrawModel m_drawModel; // ��ʾģʽ
		VRString m_strFile; // ��άͼƬ
		mutable bool m_bChange2D; // �Ƿ�ı��άͼƬ

	};

	class CEntityDrawAttributeFactory : public IAttributeFactory	
	{
	public:
		CEntityDrawAttributeFactory(void):m_strAttributeName("ʵ����Ⱦ����") { }
		virtual ~CEntityDrawAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CEntityDrawAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	
}


#endif // !_ENTITYDRAWATTRIUBTE_H_