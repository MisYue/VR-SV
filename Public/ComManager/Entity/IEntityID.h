/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体ID接口			                                        */
/* 时间： 2015-12-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYID_H_
#define _PUBLIC_IENTITYID_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityID
	{
	public:
		// 析构函数
		virtual ~IEntityID(void) { }
		// 设置ID
		virtual void SetEntityID(const uint64_t uID) = 0;
		// 获得ID
		virtual const uint64_t GetEntityID(void) const = 0;
		// 获得对应实体
		virtual IEntityBase* GetEntity(void) const = 0;
	};
}

#endif