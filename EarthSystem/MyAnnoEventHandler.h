/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ѡģ��				                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _MYANNOEVENTHANDLER_H_
#define _MYANNOEVENTHANDLER_H_

#pragma once

namespace VR_Soft
{
	class CMyAnnoEventHandler : public osgEarth::Util::AnnotationEventHandler
	{
	public:
		// ���캯��
		explicit CMyAnnoEventHandler(void);
		virtual ~CMyAnnoEventHandler(void);

	public:

		virtual void onClick( osgEarth::Util::AnnotationNode* node, const osgEarth::Util::AnnotationEventHandler::EventArgs& details );
	};
}

#endif // _MYANNOEVENTHANDLER_H_

