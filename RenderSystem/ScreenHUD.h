/************************************************************************
 作者： LJ                                                            
 用途:  抬头HUD屏幕
 时间： 2015-11-28                                                    
 修改时间:                                                            
************************************************************************/
#ifndef _SCREENHUD_H_
#define _SCREENHUD_H_

#pragma once

#include <osg/Camera>

namespace osgText
{
	class Text;
}

namespace VR_Soft
{
	class CScreenHUD  : public osg::Camera, public IScreenHUD
	{
	public:
		CScreenHUD(const VRString& strName);
		// 析构函数
		virtual ~CScreenHUD(void);

	public: 
		// 设置窗口名称
		virtual void SetHUDName(const VRString& strName) ;
		// 获得窗口名称
		virtual const VRString& GetHUDName(void) const ;
		// 移动位置
		virtual void Move(int x, int y, int width, int height) ;
		// 设置文字
		virtual void SetText(const VRString& strText) ;
		// 设置背景颜色
		virtual void SetBgColor(const float r, const float g, const float b, const float a = 1.0f) ;
		// 显示
		virtual void Show(void) ;
		// 隐藏
		virtual void Hide(void) ;
		// 显示隐藏状态
		virtual bool ShowState(void) const {return m_bShow; }

	public:
		// 调整大小
		void OnResize(int width, int height);
		// 更新文字
		void UpdateText(void);

	protected:
		// 初始化
		void Init(void);
		// test
		void Test();
		
	private:
		osgText::Text      *m_pText;
		osg::Group		   *m_pRoot;
		osg::Geode*			m_pBkGeode; // 背景
		VRString			m_strText;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		bool m_bShow;
	};
}


#endif // !_SCREENHUD_H_