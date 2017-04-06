/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备接口														*/
/* 时间： 2015-11-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IEQUIP_H_
#define _IEQUIP_H_

namespace VR_Soft
{
	class IEquip : public CEntityBaseImp<IEntityBase>
	{
	public: 
		// 析构函数
		virtual ~IEquip(void) { }
	};

	// 创建雷达对象工厂
	CREATE_ENTITYBASE_FACTORY(CreateEquipFactory);
}


#endif // !_IEQUIP_H_
