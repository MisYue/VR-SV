/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染线程，采用boot线程库                                      */
/* 时间： 2015-07-31                                                    */
/* 修改时间:						                                    */
/************************************************************************/

#ifndef _RENDERTHREAD_H_
#define _RENDERTHREAD_H_

#pragma once

#include <boost/thread.hpp>

namespace VR_Soft
{
	class CRenderThread : public CVRSoftThread
	{
	public:
		explicit CRenderThread(IViewManager* pIViewManager);
		explicit CRenderThread(void);

		~CRenderThread(void);

		// void operator() ();
	//	void Start(void);
		// 设置视图管理
		SET_GET_PROPERTY(ViewManager, IViewManager*, pI);

	public: 
		// 是否结束线程
		bool IsEndTheard(void);

	protected:
		// 执行
		void Run(void);
		// 执行结束之后
		void Exit(void);

		// 

	private:
		IViewManager* m_pIViewManager; // 视图管理
		volatile bool m_bExit;
		//boost::thread* m_pBoostThread; // 多线程
	};
}


#endif //_RENDERTHREAD_H_