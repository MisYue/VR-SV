/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ�����ͷ�ļ�����	                                        */
/* ʱ�䣺 2016-03-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLICE_IDRAWATTRIBUTEFACTORY_H_
#define _PUBLICE_IDRAWATTRIBUTEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class OSGRENDER_DLL IDrawAttributeFactory
	{
	public:
		virtual ~IDrawAttributeFactory() { }
		// ʵ����Ⱦ������
		virtual IEntityDrawManager* CreateEntityDrawManagerInstance(IEntityBase* pIEntityBase) = 0;
		// ʵ����Ⱦ
		virtual IMeshDrawAttribute* CreateMeshInstance(IEntityBase* pIEntityBase, const VRString& strDrawName) = 0;
		// �켣��
		virtual IDrawAttribute* CreateTrackLine(IEntityBase* pIEntityBase) = 0;
	};
}


#endif