/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  点选模型				                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _MYANNOEVENTHANDLER_H_
#define _MYANNOEVENTHANDLER_H_

#pragma once

namespace VR_Soft
{
	class CMyAnnoEventHandler : public osgEarth::Util::AnnotationEventHandler
	{
	public:
		// 构造函数
		explicit CMyAnnoEventHandler(void);
		virtual ~CMyAnnoEventHandler(void);

	public:

		virtual void onClick( osgEarth::Util::AnnotationNode* node, const osgEarth::Util::AnnotationEventHandler::EventArgs& details );
	};
}

#endif // _MYANNOEVENTHANDLER_H_

