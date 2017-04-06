/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���ļ�������		                                        */
/* ʱ�䣺 2016-06-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYFILEOPERATOR_H_
#define _ENTITYFILEOPERATOR_H_

#pragma once

namespace VR_Soft
{
	class CEntityFile
	{
	public:
		// ���캯��
		CEntityFile(const VRString& strPath);
		// ��������
		~CEntityFile(void);

	public:
		// ���ļ����м���
		bool Parse(void);
		// �������
		VRString GetType(void) const;
		// �������
		VRString GetName(void) const;
		// ������е�����
		ListString GetAllAttribute(void) const;
		// ������Խڵ�
		TiXmlElement* GetXmlElement(const VRString& strAttribute) const;
		// ����ʵ��
		IEntityBase* CreateEntity( const VRString& strName, const uint64_t ID );

	protected:
		// �ж��Ƿ�Ϊxml
		bool IsVaild(void);

		// �����ļ� ʵ�������Ϣ
		void ParseBaseInfo(const TiXmlElement* pElement);
		// ��������
		void ParseAttribute(TiXmlElement* pElement);

	protected:
		// ��������
		void CreateAttribute(IEntityBase* pIEntity);

	protected:
		typedef boost::unordered_map<VRString, TiXmlElement*> ListAttributes;

	private:
		VRString m_strPath;
		VRString m_strType; // ����
		VRString m_strName; // ����
		TiXmlDocument* m_pXmlDocument; // xml�ļ�
		ListAttributes m_listAttributes; // �����б�
	};
}


#endif // !_ENTITYFILEOPERATOR_H_