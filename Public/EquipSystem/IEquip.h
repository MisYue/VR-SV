/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ���ӿ�														*/
/* ʱ�䣺 2015-11-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IEQUIP_H_
#define _IEQUIP_H_

namespace VR_Soft
{
	class IEquip : public CEntityBaseImp<IEntityBase>
	{
	public: 
		// ��������
		virtual ~IEquip(void) { }
	};

	// �����״���󹤳�
	CREATE_ENTITYBASE_FACTORY(CreateEquipFactory);
}


#endif // !_IEQUIP_H_
