/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线实体接口类												*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IAIRLINEENTITY_H_
#define _PUBLIC_IAIRLINEENTITY_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL ITrajectoryLineEntity : public IEntityBase
	{
	public:
		// 析构函数
		virtual ~ITrajectoryLineEntity(void) {  }
		// 添加实体进行设置
		virtual void AddEntityBase(IEntityBase* pIEntityBase) = 0;
		// 移除实体
		virtual void RemoveEntityBase(IEntityBase* pIEntityBase) = 0;
		// 获得所有的实体
		virtual std::vector<IEntityBase* > GetAllEntity(void) const = 0;
		// 初始化航线
		// virtual void InitAirLine(IAirLine* pIAirLine) = 0;
	};
}

#endif // _PUBLIC_IAIRLINEENTITY_H_