#pragma once
#include <osgGA/GUIEventHandler>
#include "walker.h"

namespace VR_Soft
{
	/**
	 *	�����������¼��ص�
	 */
	class walkerEventHandle : public osgGA::GUIEventHandler
	{
	public:
		walkerEventHandle(Walker* walker);
		~walkerEventHandle();

		/// �����¼�����
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	private:
		Walker* _walker;		///< ����������
		double _alpha;			///< �����������alphaֵ
	};

}
