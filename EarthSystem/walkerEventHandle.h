#pragma once
#include <osgGA/GUIEventHandler>
#include "walker.h"

namespace VR_Soft
{
	/**
	 *	漫游器界面事件回调
	 */
	class walkerEventHandle : public osgGA::GUIEventHandler
	{
	public:
		walkerEventHandle(Walker* walker);
		~walkerEventHandle();

		/// 动画事件处理
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	private:
		Walker* _walker;		///< 漫游器对象
		double _alpha;			///< 渐入逐出动画alpha值
	};

}
