/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类				                                        */
/* 时间： 2016-03-23                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IENTITYBULIDER_H_
#define _PUBLIC_IENTITYBULIDER_H_

namespace VR_Soft
{
	class IEntityBase; 

	class IEntityBulider
	{
	public: 
		// 析构函数
		virtual ~IEntityBulider(void) { }
		// 创建渲染管理属性
		virtual void CreateDrawManager(void) = 0;
		// 创建渲染属性
		virtual void CreateDrawAttribute(void) = 0;
		// 创建其它的属性
		virtual void CreateAttribute(void) = 0;
		// 获得名称
		virtual VRString CreateEntityName(void) const = 0;
		// 获得产品
		virtual IEntityBase* GetEntity(void) = 0;
		// 是否创建运动属性 返回true 则创建
		virtual bool IsCreateMoveAttribute(void) = 0;
	};
}

#endif // !_PUBLIC_IENTITYBULIDER_H_