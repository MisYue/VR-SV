#define OSGRENDER_PLUGIN_EXPORT
#include "../../Public/RenderSystem/RenderSystem.h"
#include "DrawAttribute.h"
#include "EntityDrawManger.h"
#include "TracksLine.h"
#include "DrawAttributeFacoty.h"

namespace VR_Soft
{
	CDrawAttributeFactory::~CDrawAttributeFactory()
	{

	}

	IMeshDrawAttribute* CDrawAttributeFactory::CreateMeshInstance(IEntityBase* pIEntityBase, const VRString& strDrawName)
	{
		return (new CDrawAttribute(pIEntityBase, strDrawName));
	}

	// 轨迹线
	IDrawAttribute* CDrawAttributeFactory::CreateTrackLine(IEntityBase* pIEntityBase)
	{
		return (new CTracksLine(pIEntityBase));
	}

	// 实体渲染管理类
	IEntityDrawManager* CDrawAttributeFactory::CreateEntityDrawManagerInstance(IEntityBase* pIEntityBase)
	{
		CEntityDrawManger* pEntityDrawManager = new CEntityDrawManger(pIEntityBase);
		pIEntityBase->SetDrawManager(pEntityDrawManager);
		return (pEntityDrawManager);
	}

}