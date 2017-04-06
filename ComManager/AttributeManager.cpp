
#include <algorithm>
#include <vector>
#include "../../Public/VRSoft.h"
#include "AttributeItem.h"
#include "AttributeManager.h"
#include "DyLibManager.h"
#include "MoveAttribute.h"
#include "EntityDrawAttribute.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_ATTRIBUTEPLUGIN)(void);
	typedef void (*DLL_UNINSTANLL_ATTRIBUTEPLUGIN)(void);
	////////////////////////////////////

	CAttributeManager::CAttributeManager(void):
		m_uCurrentID(-1)
	{
		// ��ʼ��
		Init();
	}


	CAttributeManager::~CAttributeManager(void)
	{
		RemoveAllAttributeDll();
		RemoveAllFactory();
	}

	// ���õ�ǰ������
	void CAttributeManager::SetCurrentEntityBase(IEntityBase* pIEntityBase)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// �жϵ�ǰ���õ�ʵ���Ƿ�ΪNULL
		if (NULL == pIEntityBase)
		{
			struct ClearAttrubteUI
			{
				void operator() (IAttributeUI* pIAttributeUI)
				{
					pIAttributeUI->Clear();
				}
			};

			std::for_each(m_vecAttributeUI.begin(), m_vecAttributeUI.end(), ClearAttrubteUI());
			m_uCurrentID = -1;
			return;
		}


		m_uCurrentID = pIEntityBase->GetID();
	//	m_pICurEntityBase = pIEntityBase;

		// ���µ�������
		UpdateAttributeUI(pIEntityBase);
	}

	// �༭��ǰ��ʵ��
	void CAttributeManager::EidtCurrentEntityBase(void)
	{
		IEntityBase* pIEntityBase = IEntityManager::GetInstance().GetEntity(m_uCurrentID);
		if (NULL == pIEntityBase)
		{
			return;
		}

		pIEntityBase->EntityUpdate(ISimManager::GetInstance().GetStartTime());
	}

	// �������������
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		const VRVariant& var, const Contrl ct /*=  CTRL_EDIT*/)
	{
		// ȷ���̰߳�ȫ
		VR_MUTEX_AUTO;

		IAttributeItem* pItem = new CAttributeItem(pIAttribute, strText, strUntil, var);
		if (NULL != pItem)
		{
			CAttributeItemImp<IAttributeItem>* pItemImp = dynamic_cast<CAttributeItemImp<IAttributeItem>*>(pItem);
			if (NULL != pItemImp)
			{
				pItemImp->SetTypeName(strItemName);
				pItemImp->SetCtrlType(ct);
			}
		}

		// ������Чֵ
		return (pItem);
	}

	// �������������
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		IProperty* var, bool b , const Contrl ct /*= CTRL_SPINBOX*/)
	{
		// ȷ���̰߳�ȫ
		VR_MUTEX_AUTO;

		IAttributeItem* pItem = new CAttributeItem(pIAttribute, strText, strUntil, var);
		if (NULL != pItem)
		{
			CAttributeItemImp<IAttributeItem>* pItemImp = dynamic_cast<CAttributeItemImp<IAttributeItem>*>(pItem);
			if (NULL != pItemImp)
			{
				pItemImp->SetTypeName(strItemName);
				pItemImp->SetCtrlType(ct);
			}
		}

		// ������Чֵ
		return (pItem);
	}

	// ����������
	void CAttributeManager::UpdateAttributeItem(const IAttributeItem* pIAttributeItem)
	{
		VR_MUTEX_AUTO;

		IAttribute* pIAttribute = ((CAttributeItemImp<IAttributeItem>*)pIAttributeItem)->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}
	}

	// ����UI
	void CAttributeManager::UpdateAttributeUI(IEntityBase* pIEntityBase)
	{
		// ѭ������
		for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
		m_vecAttributeUI.end() != cstItor; ++cstItor)
		{
		(*cstItor)->ChangeEntity(pIEntityBase);
		}
	}

	// ��ӹ���
	void CAttributeManager::AddFactory( IAttributeFactory* pIAttributeFactory )
	{
		const VRString& strName = pIAttributeFactory->GetName();
		ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.find(strName);
		if (m_listAttributeFactories.end() != cstItor)
		{
			ILogManager::GetInstance().SetLogMessage(strName + "��ǰ���Թ����Ѿ�������", ERROR_ITEM_LOADED);
			return;
		}

		m_listAttributeFactories.insert(ListAttributeFactories::value_type(strName, pIAttributeFactory));
	}

	// �Ƴ�����
	void CAttributeManager::RemoveFactory( const VRString& strFactory )
	{
		// ��ѯ�Ƿ���ڵ�ǰ�Ĺ���
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "�����ڵ�ǰ�Ĺ���", ERROR_NOT_FIND);
			return;
		}

		// ��ѯ��ӵ�ǰ���Ե�ʵ��
		ListAttributeFactoriesEntities::iterator fcEntities = m_listAttributeFactoriesEntities.find(pIAttributeFactory);
		if (m_listAttributeFactoriesEntities.end() == fcEntities)
		{

			// �ӹ����б����Ƴ�
			ListAttributeFactories::iterator itor = m_listAttributeFactories.find(strFactory);
			VRSOFT_DELETE(pIAttributeFactory);
			m_listAttributeFactories.erase(itor);
			return;
		}

		struct RmFactory
		{
			VRString m_strFactory;
			RmFactory(const VRString& strFactory) : m_strFactory(strFactory) {  }
			void operator() (uint64_t ID)
			{
				IEntityManager* pIEntityManager = IEntityManager::GetInstancePtr();
				if (NULL == pIEntityManager)
				{
					return;
				}

				IEntityBase* pIEntity = pIEntityManager->GetEntity(ID);
				if (NULL != pIEntity)
				{
					pIEntity->RemoveAttribute(m_strFactory);
				}
			}
		};
		// ���ʵ��ID
		const ListEntities& listEntities = fcEntities->second;
		std::for_each(listEntities.begin(), listEntities.end(), RmFactory(strFactory));

		// �ӹ����б����Ƴ�
		ListAttributeFactories::iterator itor = m_listAttributeFactories.find(strFactory);
		VRSOFT_DELETE(pIAttributeFactory);
		m_listAttributeFactories.erase(itor);
	}

	void CAttributeManager::LoadAttributeDll( void )
	{
		// ȷ���̰߳�ȫ
		VR_MUTEX_AUTO;

		// �Ӿ���Ŀ¼����dll��̬��
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Attribute/";

		// ��ȡ��ǰĿ¼�����е��ļ�
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".dll", files);

		// ����dll��
		Files::const_iterator cstItor = files.begin();
		while (files.end() != cstItor)
		{
			const VRString& strDll = strCurPath + *cstItor;
			LoadDll(strDll);

			++cstItor;
		}

	}

	// ����dll��
	void CAttributeManager::LoadDll( const VRString& strDllPath )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��·��
		ListAttributeDlls::const_iterator cstItor = m_listAttributeDlls.find(strDllPath);
		if (m_listAttributeDlls.end() != cstItor)
		{
			return;
		}

		// ���뵱ǰ��dll��
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strDllPath);

		try
		{
			DLL_INSTANLL_ATTRIBUTEPLUGIN pDllInstanAttri = (DLL_INSTANLL_ATTRIBUTEPLUGIN)pLib->GetSymbol("DllInstallAttributePlugin");
			if (NULL == pDllInstanAttri)
			{
				ILogManager::GetInstance().SetLogMessage(strDllPath + "���Լ���ʧ��,δ�ҵ����DllInstallAttributePlugin", ERROR_NOT_FIND);
				return;
			}

			// ���ز��
			m_listAttributeDlls.insert(ListAttributeDlls::value_type(strDllPath, pLib));

			// ���ز��
			pDllInstanAttri();
		}
		catch (...)
		{
			ILogManager::GetInstance().SetLogMessage(strDllPath + "�������Բ��", ERROR_NOT_COM);
		}

	}

	// �Ƴ�dll��
	void CAttributeManager::RemoveAttributeDll( const VRString& strDll )
	{
		// ���߳�ͬ��
		VR_MUTEX_AUTO

			// ��ѯ
		ListAttributeDlls::iterator itor = m_listAttributeDlls.find(strDll);
		if (m_listAttributeDlls.end() != itor)
		{
			try
			{
				DLL_UNINSTANLL_ATTRIBUTEPLUGIN pDllUnInstanAttri = (DLL_UNINSTANLL_ATTRIBUTEPLUGIN)itor->second->GetSymbol("DllUnInstallAttributePlugin");
				if (NULL == pDllUnInstanAttri)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "���Բ��δ�ҵ�ж�ؽӿ�DllUnInstallAttributePlugin", ERROR_NOT_FIND);
					return;
				}

				// ���ز��
				pDllUnInstanAttri();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "�������Բ��", ERROR_NOT_COM);
			}

			CDyLibManager::GetInstance().Unload(itor->second);
			m_listAttributeDlls.erase(itor);
		}
	}

	// ��ȡ���е�dllָ������
	ListString CAttributeManager::GetAllAttributeDll( void ) const
	{
		ListString listString;

		// �������е�����
		for (ListAttributeDlls::const_iterator cstItor = m_listAttributeDlls.begin(); \
			m_listAttributeDlls.end() != cstItor; ++cstItor)
		{
			listString.push_back(cstItor->first);
		}

		return (listString);
	}

	// �����������
	ListString CAttributeManager::GetAllAttribute( void ) const
	{
		ListString listString;

		// �������е�����
		for (ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.begin(); \
			m_listAttributeFactories.end() != cstItor; ++cstItor)
		{
			listString.push_back(cstItor->first);
		}

		return (listString);
	}

	// ��ʵ������
	bool CAttributeManager::BindAttribute( IEntityBase* pIEntityBase, const VRString& strFactory )
	{
		// ��ѯ�����Ƿ����
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "�����ڵ�ǰ�Ĺ���", ERROR_NOT_FIND);
			return (false);
		}

		// ����ģ������
		IAttribute* pIAttribute = pIAttributeFactory->CreateInstance(pIEntityBase);
		if (NULL == pIAttribute)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "����ʵ��ʧ��", ERROR_MALLOC);
			return (false);
		}

		// �������
		pIEntityBase->AddAttributes(pIAttribute);
	/*	IDrawAttribute* pIDrawAttribute = dynamic_cast<IDrawAttribute*>(pIAttribute);
		if (NULL != pIDrawAttribute)
		{
			pIEntityBase->AddDrawAttribute(pIDrawAttribute);
		}
		else
		{
			
		}*/

		// �жϹ���ģ���Ƿ���ֵ
		ListAttributeFactoriesEntities::iterator itor = m_listAttributeFactoriesEntities.find(pIAttributeFactory);
		if (m_listAttributeFactoriesEntities.end() == itor)
		{
			ListEntities listEntities;
			listEntities.push_back(pIEntityBase->GetID());

			m_listAttributeFactoriesEntities.insert(ListAttributeFactoriesEntities::value_type(pIAttributeFactory, listEntities));
		}
		else
		{
			ListEntities& listEntities = itor->second;
			listEntities.push_back(pIEntityBase->GetID());
		}

		return (true);
	}

	// ��ʵ������
	bool CAttributeManager::BindAttribute( IEntityBase* pIEntityBase, IAttribute* pIAttribute )
	{
		// �ж������Ƿ����
		if (NULL == pIAttribute)
		{
			return (false);
		}

		if (m_uCurrentID == pIEntityBase->GetID())
		{
			// ��Ӹ���
			for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
				m_vecAttributeUI.end() != cstItor; ++cstItor)
			{
				(*cstItor)->UpdateNewItem(pIAttribute);
			}
		}

		return (true);
	}

	// �Ӵ���
	bool CAttributeManager::UnBindAttribute( IEntityBase* pIEntityBase, const VRString& strFactory )
	{
		// ��ѯ�����Ƿ����
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "�����ڵ�ǰ�Ĺ���", ERROR_NOT_FIND);
			return (false);
		}

		// �Ƴ�����ģ������
		return (pIEntityBase->RemoveAttribute(strFactory));
	}

	// �����
	bool CAttributeManager::UnBindAttribute( IEntityBase* pIEntityBase, IAttribute* pIAttribute )
	{
		// �ж��Ƿ�Ϊ��
		if (NULL == pIAttribute)
		{
			return (false);
		}

		if (m_uCurrentID == pIEntityBase->GetID())
		{
			// ��Ӹ���
			for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
				m_vecAttributeUI.end() != cstItor; ++cstItor)
			{
				(*cstItor)->UpdateDelItem(pIAttribute);
			}
		}

		return (true);
	}

	// ��ù���
	IAttributeFactory* CAttributeManager::GetFactory( const VRString& strFactory ) const
	{
		// ��ѯ�Ƿ���ڵ�ǰ�Ĺ���
		ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.find(strFactory);
		if (m_listAttributeFactories.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);

	}

	// ɾ�����еĿ�
	void CAttributeManager::RemoveAllAttributeDll( void )
	{
		// ��ѯ
		for (ListAttributeDlls::iterator itor = m_listAttributeDlls.begin();
			m_listAttributeDlls.end() != itor; ++itor )
		{
			const VRString strDll = itor->first;
			try
			{
				DLL_UNINSTANLL_ATTRIBUTEPLUGIN pDllUnInstanAttri = (DLL_UNINSTANLL_ATTRIBUTEPLUGIN)itor->second->GetSymbol("DllUnInstallAttributePlugin");
				if (NULL == pDllUnInstanAttri)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "���Բ��δ�ҵ�ж�ؽӿ�DllUnInstallAttributePlugin", ERROR_NOT_FIND);
					return;
				}

				// ���ز��
				pDllUnInstanAttri();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "�������Բ��", ERROR_NOT_COM);
			}

			CDyLibManager::GetInstance().Unload(itor->second);
		}

		m_listAttributeDlls.clear();

	}

	void CAttributeManager::Attach( IAttributeUI* pIAttributeUI )
	{
		m_vecAttributeUI.insert(pIAttributeUI);

		// ��õ�ǰ�Ļʵ���Ƿ�
		IEntityBase* pICurrentEntity = IEntityManager::GetInstance().GetEntity(m_uCurrentID);
		if (NULL == pICurrentEntity)
		{
			return;
		}

		pIAttributeUI->ChangeEntity(pICurrentEntity);
	}

	// �Ƴ��۲���
	void CAttributeManager::Detach( IAttributeUI* pIAttributeUI )
	{
		pIAttributeUI->Clear();

		VctAttributeUI::iterator itor = m_vecAttributeUI.find(pIAttributeUI);
		if (m_vecAttributeUI.end() != itor)
		{
			m_vecAttributeUI.erase(itor);
		}
	}

	// ��õ�ǰ�����ʵ��
	IEntityBase* CAttributeManager::GetCurrentEntityBase( void ) const
	{
		return (IEntityManager::GetInstance().GetEntity(m_uCurrentID));
	}

	// ��õ�ǰ�����ʵ��ID
	uint64_t CAttributeManager::GetCurrentEntityBaseID( void ) const
	{
		return (m_uCurrentID);
	}

	// ��ʼ��
	void CAttributeManager::Init(void)
	{
		// ����˶�����
		IAttributeFactory* pIAttributeFactory = new CMoveAttributeFactory;
		AddFactory(pIAttributeFactory);

		// ���ʵ����Ⱦ����
		pIAttributeFactory = new CEntityDrawAttributeFactory;
		AddFactory(pIAttributeFactory);

		LoadAttributeDll();
	}

	// �Ƴ����е����Թ���
	void CAttributeManager::RemoveAllFactory( void )
	{
		// �������е����Թ���
		for (ListAttributeFactories::iterator FactoryItor = m_listAttributeFactories.begin(); m_listAttributeFactories.end() != FactoryItor; ++FactoryItor)
		{
			// ��ѯ��ӵ�ǰ���Ե�ʵ��
			ListAttributeFactoriesEntities::iterator fcEntities = m_listAttributeFactoriesEntities.find(FactoryItor->second);
			if (m_listAttributeFactoriesEntities.end() == fcEntities)
			{
				VRSOFT_DELETE(FactoryItor->second);
				continue;
			}

			struct RmFactory
			{
				VRString m_strFactory;
				RmFactory(const VRString& strFactory) : m_strFactory(strFactory) {  }
				void operator() (uint64_t ID)
				{
					IEntityManager* pIEntityManager = IEntityManager::GetInstancePtr();
					if (NULL == pIEntityManager)
					{
						return;
					}

					IEntityBase* pIEntity = pIEntityManager->GetEntity(ID);
					if (NULL != pIEntity)
					{
						pIEntity->RemoveAttribute(m_strFactory);
					}
				}
			};
			// ���ʵ��ID
			const ListEntities& listEntities = fcEntities->second;
			std::for_each(listEntities.begin(), listEntities.end(), RmFactory(FactoryItor->first));

			// �ӹ����б����Ƴ�
			VRSOFT_DELETE(FactoryItor->second);
		}

		m_listAttributeFactories.clear();
		
	}

}

