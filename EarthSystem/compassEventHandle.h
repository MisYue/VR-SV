#pragma once
#include <osgGA/GUIEventHandler>
#include "compass.h"

namespace VR_Soft
{
	/**
	 *	���̽����¼��ص�
	 */
	class compassEventHandle : public osgGA::GUIEventHandler
	{
	public:
		compassEventHandle(Compass* compass);
		~compassEventHandle();

		/// �����¼�����
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	private:
		Compass* _compass;		///< ���̶���
		double _alpha;			///< �������alphaֵ
	};
}