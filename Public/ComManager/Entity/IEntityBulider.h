/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����				                                        */
/* ʱ�䣺 2016-03-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IENTITYBULIDER_H_
#define _PUBLIC_IENTITYBULIDER_H_

namespace VR_Soft
{
	class IEntityBase; 

	class IEntityBulider
	{
	public: 
		// ��������
		virtual ~IEntityBulider(void) { }
		// ������Ⱦ��������
		virtual void CreateDrawManager(void) = 0;
		// ������Ⱦ����
		virtual void CreateDrawAttribute(void) = 0;
		// ��������������
		virtual void CreateAttribute(void) = 0;
		// �������
		virtual VRString CreateEntityName(void) const = 0;
		// ��ò�Ʒ
		virtual IEntityBase* GetEntity(void) = 0;
		// �Ƿ񴴽��˶����� ����true �򴴽�
		virtual bool IsCreateMoveAttribute(void) = 0;
	};
}

#endif // !_PUBLIC_IENTITYBULIDER_H_