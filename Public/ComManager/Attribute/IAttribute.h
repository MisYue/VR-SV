/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Ի���			                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IATTRIBUT_H_
#define _IATTRIBUT_H_

#include <list>

namespace VR_Soft
{
	class IEntityBase;
	class IAttributeItem;

	class VRSOFT_DLL IAttribute
	{
	public:
		typedef std::vector<IAttributeItem* > ListAttrItems;

	public:
		// ��������
		virtual ~IAttribute() { }
		// ��ʼ������
		virtual void Init(void) = 0;
		// ���ģ�Ͷ���
		virtual IEntityBase* GetEntity(void) const = 0;
		// �������
		virtual const VRString& GetName(void) const = 0;
		// ��������
		virtual void SetName(const VRString& strName) = 0;
		// ��������б�
		virtual ListAttrItems GetAttrItems(void) const = 0;
		// ͨ�����Ե����ƻ�ȡ������
		virtual IAttributeItem* GetItem(const VRString& strName) const = 0;
		// ��������
		virtual void AddAttrItem(IAttributeItem* pIItem) = 0;
		// ����
		virtual void Update(void) = 0;
		// ��ȡXML�ļ�
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement) = 0;
		// ����XML�ڵ�
		virtual void SaveXmlNode(TiXmlElement* pTiXmlElement) const = 0;
	};
}

#endif // _IATTRIBUT_H_