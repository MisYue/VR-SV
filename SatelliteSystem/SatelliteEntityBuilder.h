/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星实体构造器												*/
/* 时间： 2016-04-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _SATELLITEENTITYBUILDER_H_
#define _SATELLITEENTITYBUILDER_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteEntity;

	class CSatelliteEntityBuilder : public IEntityBulider
	{
	public:
		// 构造函数
		CSatelliteEntityBuilder(void);
		// 析构函数
		virtual ~CSatelliteEntityBuilder(void);

	public:
		// 创建渲染管理属性
		virtual void CreateDrawManager(void);
		// 创建渲染属性
		virtual void CreateDrawAttribute(void);
		// 创建其它的属性
		virtual void CreateAttribute(void) ;
		// 获得名称
		virtual VRString CreateEntityName(void) const ;
		// 获得产品
		virtual IEntityBase* GetEntity(void);
		// 是否创建运动属性 返回true 则创建
		virtual bool IsCreateMoveAttribute(void) ;

	private:
		CSatelliteEntity* m_pSatelliteEntity;
		static unsigned int m_index;
	};

	// 注册工厂
	REGISTER_BASEENTITY_FACTORY(CSatelliteEntityBuilder, "卫星");
}


#endif // !_SATELLITEENTITYBUILDER_H_