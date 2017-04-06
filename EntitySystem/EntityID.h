/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体ID实现类			                                        */
/* 时间： 2015-12-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENTITYID_H_
#define _ENTITYID_H_

#pragma once

namespace VR_Soft
{
	class CEntityID : public IEntityID
	{
	public:
		// 构造函数
		explicit CEntityID(IEntityBase* pIEntityBase, const uint64_t ID);
		// 析构函数
		virtual ~CEntityID(void);

		// 赋值操作符号
		virtual CEntityID& operator= (const CEntityID& other);

	public:
		// 设置ID
		virtual void SetEntityID(const uint64_t uID) ;
		// 获得ID
		virtual const uint64_t GetEntityID(void) const;
		// 获得对应实体
		virtual IEntityBase* GetEntity(void) const ;

	private:
		uint64_t m_uID; // 唯一标志
		IEntityBase* m_pIEntityBase; // 对应实体
	};
}


#endif // !_ENTITYID_H_