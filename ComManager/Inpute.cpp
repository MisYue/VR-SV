#include "../../Public/VRSoft.h"
#include "Inpute.h"

namespace VR_Soft
{
	// 构造函数
	CInpute::CInpute(void)
	{
		Init();
	}

	// 析构函数
	CInpute::~CInpute(void)
	{
	}

	// 初始化
	void CInpute::Init(void)
	{
		m_vPosition2D = osg::Vec2d(0.0, 0.0);
		m_mouseSymbol = MS_NULL;
		m_keySymbol = KEY_NULL;
	}

	// 获得鼠标是否单击
	bool CInpute::GetMouseButton(const MouseSymbol mouseSymbol) const
	{
		if (m_mouseSymbol == mouseSymbol)
		{
			return (true);
		}

		return (false);
	}

	// 获得是否安装键盘
	bool CInpute::GetKey(const KeySymbol keySymbol) const
	{
		if (m_keySymbol == keySymbol)
		{
			return (true);
		}

		return (false);
	}

	// 获得鼠标的二维位置
	osg::Vec2d CInpute::GetMousePosition2D(void) const
	{
		return (m_vPosition2D);
	}

	// 设置鼠标
	void CInpute::SetMouseButton(const MouseSymbol mouseSymbol)
	{
		m_mouseSymbol = mouseSymbol;
	}

	// 设置是否安装键盘
	void CInpute::SetKey(const KeySymbol keySymbol)
	{
		m_keySymbol = keySymbol;
	}

	// 设置点坐标
	void CInpute::SetMousePosition2D(const osg::Vec2d vPos)
	{
		m_vPosition2D = vPos;
	}

}
