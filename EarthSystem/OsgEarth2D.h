/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth����		                                            */
/* ʱ�䣺 2016-06-30                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _OSGEARTH2D_H_
#define _OSGEARTH2D_H_

#pragma once

#include "OsgEarth.h"

namespace VR_Soft
{
	class COsgEarth2D : public COsgEarth
	{
	public:
		explicit COsgEarth2D();
		~COsgEarth2D(void);

	public:
		// �����ͼ
		virtual void Attach(IRenderView* pIRenderView);

	public:
		// ���ʵ��
		virtual void AddEntity(IEntityBase* pIEntity);
		// ��Ӽ�����Ⱦ��
		virtual void AddFeatureGeomtry(const IFeatureGeomtry* pIFeatureGoemtry);
		// ���õ�������
		virtual osgEarth::MapNode* InitMapNode(osgEarth::MapNode* pNodeMap);

	protected:
		
	};
}


#endif // !_OSGEARTH2D_H_