/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  事件接口模板		                                            */
/* 时间： 2015-08-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _EVENTIMP_H_
#define _EVENTIMP_H_


namespace VR_Soft
{
	template <class T>
	class CEventImp : public T
	{
	public:
		virtual ~CEventImp() { }

	public:
		// 鼠标左键单击事件
		virtual void OnClick(void) { }
		// 鼠标左键按下
		virtual void OnLButtonDown(const float x, const float y) { }
		// 鼠标左键弹起
		virtual void OnLButtonUp(const float x, const float y) { }
		// 鼠标右键按下
		virtual void OnRButtonDown(const float x, const float y) { }
		// 鼠标右键弹起
		virtual void OnRButtonUp(const float x, const float y) { }
		// 键盘按下
		virtual void OnKeyDown(int key) { }
	};
}

#endif // _EVENTIMP_H_