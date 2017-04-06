#pragma once
#include <osgGA/GUIEventHandler>
#include "zoom.h"

namespace VR_Soft
{
	/**
	 *	缩放器界面事件回调
	 */
	class zoomEventHandle : public osgGA::GUIEventHandler
	{
	public:
		zoomEventHandle(Zoom* zoom);
		~zoomEventHandle();

		/// 动画事件处理
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&aa);
	private:
		Zoom* _zoom;			///< 缩放器对象
		double _alpha;			///< 渐入逐出alpha值
	};
}
