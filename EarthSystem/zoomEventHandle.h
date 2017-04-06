#pragma once
#include <osgGA/GUIEventHandler>
#include "zoom.h"

namespace VR_Soft
{
	/**
	 *	�����������¼��ص�
	 */
	class zoomEventHandle : public osgGA::GUIEventHandler
	{
	public:
		zoomEventHandle(Zoom* zoom);
		~zoomEventHandle();

		/// �����¼�����
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&aa);
	private:
		Zoom* _zoom;			///< ����������
		double _alpha;			///< �������alphaֵ
	};
}
