/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�������			                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IENTITYCOMPONENT_H_
#define _IENTITYCOMPONENT_H_

namespace VR_Soft
{
	class IEntityBase;
	class IEntityBaseFactory;

	class VRSOFT_DLL IEntityComponent 
	{
	public:
		// ���캯��
		explicit IEntityComponent(): m_strName(""), m_strPath(""), m_pParentEntity(NULL)
		{
		}
		// ��������
		virtual ~IEntityComponent() 
		{
		}
		// ��������
		virtual void SetName(const VRString& strName) 
		{
			m_strName = strName;
		}

		// �������
		virtual VRString GetName(void) const
		{
			return (m_strName);
		}

		// ����·��
		virtual void SetPath(const VRString& strPath) { m_strPath = strPath; }
		// ���·��
		virtual VRString GetPath(void) const { return (m_strPath); }
		// ���ø�����
		virtual void SetParentEntity(IEntityComponent* pIEntityManager) { m_pParentEntity = pIEntityManager; }
		// ��ø�����
		virtual IEntityComponent* GetParentEntity(void) { return (m_pParentEntity); }
		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt) { }
		// �Ƿ����Ӽ�
		virtual bool IsExport(void) { return (false); }

	protected:
		VRString m_strName; // ����
		VRString m_strPath; // ·�� ��ֹ����γɻ�·
		IEntityComponent* m_pParentEntity; // ������
	};
}

#endif // _IENTITYCOMPONENT_H_