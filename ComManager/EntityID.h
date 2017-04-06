/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��IDʵ����			                                        */
/* ʱ�䣺 2015-12-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENTITYID_H_
#define _ENTITYID_H_

#pragma once

namespace VR_Soft
{
	class CEntityID : public IEntityID
	{
	public:
		// ���캯��
		explicit CEntityID(IEntityBase* pIEntityBase, const uint64_t ID);
		// ��������
		virtual ~CEntityID(void);

		// ��ֵ��������
		virtual CEntityID& operator= (const CEntityID& other);

	public:
		// ����ID
		virtual void SetEntityID(const uint64_t uID) ;
		// ���ID
		virtual const uint64_t GetEntityID(void) const;
		// ��ö�Ӧʵ��
		virtual IEntityBase* GetEntity(void) const ;

	private:
		uint64_t m_uID; // Ψһ��־
		IEntityBase* m_pIEntityBase; // ��Ӧʵ��
	};
}


#endif // !_ENTITYID_H_