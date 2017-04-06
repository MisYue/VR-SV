/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ�����ͷ�ļ�����	                                        */
/* ʱ�䣺 2016-03-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _DRAWATTRIBUTEFACTORY_H_
#define _DRAWATTRIBUTEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CDrawAttributeFactory : public IDrawAttributeFactory
	{
	public:
		virtual ~CDrawAttributeFactory();
		// ʵ����Ⱦ������
		virtual IEntityDrawManager* CreateEntityDrawManagerInstance(IEntityBase* pIEntityBase);
		// ʵ����Ⱦ
		virtual IMeshDrawAttribute* CreateMeshInstance(IEntityBase* pIEntityBase, const VRString& strDrawName);
		// �켣��
		virtual IDrawAttribute* CreateTrackLine(IEntityBase* pIEntityBase);
	};
}


#endif