/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��ID�ӿ�			                                        */
/* ʱ�䣺 2015-12-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYID_H_
#define _PUBLIC_IENTITYID_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityID
	{
	public:
		// ��������
		virtual ~IEntityID(void) { }
		// ����ID
		virtual void SetEntityID(const uint64_t uID) = 0;
		// ���ID
		virtual const uint64_t GetEntityID(void) const = 0;
		// ��ö�Ӧʵ��
		virtual IEntityBase* GetEntity(void) const = 0;
	};
}

#endif