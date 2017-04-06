/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真类	                                                    */
/* 时间： 2016-04-08                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SIMSINGLETHREAD_H_
#define _SIMSINGLETHREAD_H_

#pragma once

namespace VR_Soft
{
	class CEntityThread : public CVRSoftThread
	{
	public:
		// 构造函数
		CEntityThread(void);
		// 析构函数
		virtual ~CEntityThread(void);


	protected:
		// 运行线程
		virtual void Run(void);
	};

}

#endif // ! _SIMSINGLETHREAD_H_