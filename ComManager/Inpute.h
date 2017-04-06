/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  输入设备管理			                                        */
/* 时间： 2016-04-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _INPUTE_H_
#define _INPUTE_H_

namespace VR_Soft
{
	class CInpute : public IEvent
	{
	public:
		// 构造函数
		CInpute(void);
		// 析构函数
		virtual ~CInpute(void);

	public:
		// 初始化
		virtual void Init(void) ;
		// 获得鼠标是否单击
		virtual bool GetMouseButton(const MouseSymbol mouseSymbol) const ;
		// 获得是否安装键盘
		virtual bool GetKey(const KeySymbol keySymbol) const ;
		// 获得鼠标的二维位置
		virtual osg::Vec2d GetMousePosition2D(void) const ;
		// 设置鼠标
		virtual void SetMouseButton(const MouseSymbol mouseSymbol);
		// 设置是否安装键盘
		virtual void SetKey(const KeySymbol keySymbol) ;
		// 设置点坐标
		virtual void SetMousePosition2D(const osg::Vec2d vPos);

	private:
		osg::Vec2d m_vPosition2D; // 二维点
		KeySymbol m_keySymbol; // 按下键盘
		MouseSymbol m_mouseSymbol; // 按下鼠标
	};
}

#endif // !_INPUTE_H_