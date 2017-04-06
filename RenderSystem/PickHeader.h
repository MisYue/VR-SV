#ifndef _PICKHEADER_H_
#define _PICKHEADER_H_

#pragma once

namespace VR_Soft
{
	class CRenderView;

	class CPickHeader : public osgGA::GUIEventHandler
	{
	public:
		// 构造函数
		explicit CPickHeader(CRenderView* pRenderView);
		virtual ~CPickHeader(void);

	public:
		virtual  bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
		virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);

	public:
		// 更新屏幕窗口
		void Resize(int width, int height);

	private:
		bool m_bClick;
		CRenderView* m_pRenderView;
	};
}


#endif // _PICKHEADER_H_