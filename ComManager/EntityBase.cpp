
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "EntityBase.h"

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	// ���캯��
	CEntityBase::CEntityBase(void)
	{
	}

	// ��������
	CEntityBase::~CEntityBase(void)
	{
	}

	// ��ʼ��
	void CEntityBase::Init( void )
	{

	}

	// ��ʼ��״̬��
	void CEntityBase::InitStateMachine( IStateMachine* pIStateMachine )
	{

	}

	// �������
	const VRString CEntityBase::GetEntityType( void ) const
	{
		return ("ϵͳģ��");
	}

	////////////////////////////ϵͳģ��������//////////////////////////////////////////////
	// ���캯��
	CEntityBaseBuilder::CEntityBaseBuilder( void )
	{
		m_pEntityBase = new CEntityBase;
	}

	// ��������
	CEntityBaseBuilder::~CEntityBaseBuilder( void )
	{

	}

	// ������Ⱦ��������
	void CEntityBaseBuilder::CreateDrawManager( void )
	{
		// �����Ⱦ���
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pEntityBase);
	}

	// ������Ⱦ����
	void CEntityBaseBuilder::CreateDrawAttribute( void )
	{

	}

	// ��������������
	void CEntityBaseBuilder::CreateAttribute( void )
	{

	}

	// �������
	VRString CEntityBaseBuilder::CreateEntityName( void ) const
	{
		VRString strName = m_pEntityBase->GetEntityType();
		// ģ�͸���
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

	// ��ò�Ʒ
	IEntityBase* CEntityBaseBuilder::GetEntity( void )
	{
		return (m_pEntityBase);
	}

	// �Ƿ񴴽��˶����� ����true �򴴽�
	bool CEntityBaseBuilder::IsCreateMoveAttribute( void )
	{
		return (true);
	}

	

}
