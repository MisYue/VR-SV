/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体导演类			                                        */
/* 时间： 2016-03-23                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ENTITYDIRCTOR_H_
#define _ENTITYDIRCTOR_H_

#pragma once

namespace VR_Soft
{
	class CEntityDirctor
	{
	public:
		// 构造函数
		CEntityDirctor(IEntityBulider* pIEntityBulider);
		// 析构函数
		~CEntityDirctor(void);

		// 生成
		IEntityBase* Construct();

	private:
		IEntityBulider* m_pIEntityBulider;
	};
}


#endif //! _ENTITYDIRCTOR_H_