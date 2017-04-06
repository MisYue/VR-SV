#pragma once
#include <osgGA/GUIEventHandler>
#include "compass.h"

namespace VR_Soft
{
	/**
	 *	罗盘界面事件回调
	 */
	class compassEventHandle : public osgGA::GUIEventHandler
	{
	public:
		compassEventHandle(Compass* compass);
		~compassEventHandle();

		/// 动画事件处理
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	private:
		Compass* _compass;		///< 罗盘对象
		double _alpha;			///< 渐入逐出alpha值
	};
}