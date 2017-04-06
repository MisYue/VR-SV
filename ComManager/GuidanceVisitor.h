/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  根据规矩点运动类		                                        */
/* 时间： 2016-06-06                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _GUIDANCEVISITOR_H_
#define _GUIDANCEVISITOR_H_

#pragma once

namespace VR_Soft
{
	class CGuidanceVisitor : public IEntityVisitor
	{
	public:
		// 构造函数
		CGuidanceVisitor(void);
		// 析构函数
		virtual ~CGuidanceVisitor(void);

	public:
		// 设置点数据
		void SetTrajectory(ITrajectory* pITrajctory);

	public:
		// 访问器
		virtual void Visit(IEntityBase* pIEntityBase);

	private:
		ITrajectory* m_pITrajectory;
		IEntityBaseAttribute* m_pIEntityBaseAttribute; // 模型基本属性
	};
}


#endif // !_GUIDANCEVISITOR_H_