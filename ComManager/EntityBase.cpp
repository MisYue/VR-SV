
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "EntityBase.h"

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	// 构造函数
	CEntityBase::CEntityBase(void)
	{
	}

	// 析构函数
	CEntityBase::~CEntityBase(void)
	{
	}

	// 初始化
	void CEntityBase::Init( void )
	{

	}

	// 初始化状态机
	void CEntityBase::InitStateMachine( IStateMachine* pIStateMachine )
	{

	}

	// 获得类型
	const VRString CEntityBase::GetEntityType( void ) const
	{
		return ("系统模型");
	}

	////////////////////////////系统模型生成器//////////////////////////////////////////////
	// 构造函数
	CEntityBaseBuilder::CEntityBaseBuilder( void )
	{
		m_pEntityBase = new CEntityBase;
	}

	// 析构函数
	CEntityBaseBuilder::~CEntityBaseBuilder( void )
	{

	}

	// 创建渲染管理属性
	void CEntityBaseBuilder::CreateDrawManager( void )
	{
		// 获得渲染组件
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pEntityBase);
	}

	// 创建渲染属性
	void CEntityBaseBuilder::CreateDrawAttribute( void )
	{

	}

	// 创建其它的属性
	void CEntityBaseBuilder::CreateAttribute( void )
	{

	}

	// 获得名称
	VRString CEntityBaseBuilder::CreateEntityName( void ) const
	{
		VRString strName = m_pEntityBase->GetEntityType();
		// 模型个数
		int nSize = IEntityManager::GetInstance().GetCount();

		try
		{
			VRString str = boost::lexical_cast<VRString>(nSize);
			strName += str;
		}
		catch(...)
		{
		} 
		
		return (strName);
	}

	// 获得产品
	IEntityBase* CEntityBaseBuilder::GetEntity( void )
	{
		return (m_pEntityBase);
	}

	// 是否创建运动属性 返回true 则创建
	bool CEntityBaseBuilder::IsCreateMoveAttribute( void )
	{
		return (true);
	}

	

}
