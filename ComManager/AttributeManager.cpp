
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
	// 注册回调函数
	typedef void (*DLL_INSTANLL_ATTRIBUTEPLUGIN)(void);
	typedef void (*DLL_UNINSTANLL_ATTRIBUTEPLUGIN)(void);
	////////////////////////////////////

	CAttributeManager::CAttributeManager(void):
		m_uCurrentID(-1)
	{
		// 初始化
		Init();
	}


	CAttributeManager::~CAttributeManager(void)
	{
		RemoveAllAttributeDll();
		RemoveAllFactory();
	}

	// 设置当前的属性
	void CAttributeManager::SetCurrentEntityBase(IEntityBase* pIEntityBase)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 判断当前设置的实体是否为NULL
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

		// 更新到界面中
		UpdateAttributeUI(pIEntityBase);
	}

	// 编辑当前的实体
	void CAttributeManager::EidtCurrentEntityBase(void)
	{
		IEntityBase* pIEntityBase = IEntityManager::GetInstance().GetEntity(m_uCurrentID);
		if (NULL == pIEntityBase)
		{
			return;
		}

		pIEntityBase->EntityUpdate(ISimManager::GetInstance().GetStartTime());
	}

	// 创建属性项对象
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		const VRVariant& var, const Contrl ct /*=  CTRL_EDIT*/)
	{
		// 确保线程安全
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

		// 返回有效值
		return (pItem);
	}

	// 创建属性项对象
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		IProperty* var, bool b , const Contrl ct /*= CTRL_SPINBOX*/)
	{
		// 确保线程安全
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

		// 返回有效值
		return (pItem);
	}

	// 更新属性项
	void CAttributeManager::UpdateAttributeItem(const IAttributeItem* pIAttributeItem)
	{
		VR_MUTEX_AUTO;

		IAttribute* pIAttribute = ((CAttributeItemImp<IAttributeItem>*)pIAttributeItem)->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}
	}

	// 更新UI
	void CAttributeManager::UpdateAttributeUI(IEntityBase* pIEntityBase)
	{
		// 循环更新
		for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
		m_vecAttributeUI.end() != cstItor; ++cstItor)
		{
		(*cstItor)->ChangeEntity(pIEntityBase);
		}
	}

	// 添加工厂
	void CAttributeManager::AddFactory( IAttributeFactory* pIAttributeFactory )
	{
		const VRString& strName = pIAttributeFactory->GetName();
		ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.find(strName);
		if (m_listAttributeFactories.end() != cstItor)
		{
			ILogManager::GetInstance().SetLogMessage(strName + "当前属性工厂已经被加载", ERROR_ITEM_LOADED);
			return;
		}

		m_listAttributeFactories.insert(ListAttributeFactories::value_type(strName, pIAttributeFactory));
	}

	// 移除工厂
	void CAttributeManager::RemoveFactory( const VRString& strFactory )
	{
		// 查询是否存在当前的工厂
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "不存在当前的工厂", ERROR_NOT_FIND);
			return;
		}

		// 查询添加当前属性的实体
		ListAttributeFactoriesEntities::iterator fcEntities = m_listAttributeFactoriesEntities.find(pIAttributeFactory);
		if (m_listAttributeFactoriesEntities.end() == fcEntities)
		{

			// 从工厂列表中移除
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
		// 获得实体ID
		const ListEntities& listEntities = fcEntities->second;
		std::for_each(listEntities.begin(), listEntities.end(), RmFactory(strFactory));

		// 从工厂列表中移除
		ListAttributeFactories::iterator itor = m_listAttributeFactories.find(strFactory);
		VRSOFT_DELETE(pIAttributeFactory);
		m_listAttributeFactories.erase(itor);
	}

	void CAttributeManager::LoadAttributeDll( void )
	{
		// 确保线程安全
		VR_MUTEX_AUTO;

		// 从具体目录加载dll动态库
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Attribute/";

		// 获取当前目录下所有的文件
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".dll", files);

		// 加载dll库
		Files::const_iterator cstItor = files.begin();
		while (files.end() != cstItor)
		{
			const VRString& strDll = strCurPath + *cstItor;
			LoadDll(strDll);

			++cstItor;
		}

	}

	// 导入dll库
	void CAttributeManager::LoadDll( const VRString& strDllPath )
	{
		// 查询是否存在当前的路径
		ListAttributeDlls::const_iterator cstItor = m_listAttributeDlls.find(strDllPath);
		if (m_listAttributeDlls.end() != cstItor)
		{
			return;
		}

		// 加入当前的dll库
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strDllPath);

		try
		{
			DLL_INSTANLL_ATTRIBUTEPLUGIN pDllInstanAttri = (DLL_INSTANLL_ATTRIBUTEPLUGIN)pLib->GetSymbol("DllInstallAttributePlugin");
			if (NULL == pDllInstanAttri)
			{
				ILogManager::GetInstance().SetLogMessage(strDllPath + "属性加载失败,未找到入口DllInstallAttributePlugin", ERROR_NOT_FIND);
				return;
			}

			// 加载插件
			m_listAttributeDlls.insert(ListAttributeDlls::value_type(strDllPath, pLib));

			// 加载插件
			pDllInstanAttri();
		}
		catch (...)
		{
			ILogManager::GetInstance().SetLogMessage(strDllPath + "不是属性插件", ERROR_NOT_COM);
		}

	}

	// 移除dll库
	void CAttributeManager::RemoveAttributeDll( const VRString& strDll )
	{
		// 多线程同步
		VR_MUTEX_AUTO

			// 查询
		ListAttributeDlls::iterator itor = m_listAttributeDlls.find(strDll);
		if (m_listAttributeDlls.end() != itor)
		{
			try
			{
				DLL_UNINSTANLL_ATTRIBUTEPLUGIN pDllUnInstanAttri = (DLL_UNINSTANLL_ATTRIBUTEPLUGIN)itor->second->GetSymbol("DllUnInstallAttributePlugin");
				if (NULL == pDllUnInstanAttri)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "属性插件未找到卸载接口DllUnInstallAttributePlugin", ERROR_NOT_FIND);
					return;
				}

				// 加载插件
				pDllUnInstanAttri();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "不是属性插件", ERROR_NOT_COM);
			}

			CDyLibManager::GetInstance().Unload(itor->second);
			m_listAttributeDlls.erase(itor);
		}
	}

	// 获取所有的dll指令名称
	ListString CAttributeManager::GetAllAttributeDll( void ) const
	{
		ListString listString;

		// 遍历所有的属性
		for (ListAttributeDlls::const_iterator cstItor = m_listAttributeDlls.begin(); \
			m_listAttributeDlls.end() != cstItor; ++cstItor)
		{
			listString.push_back(cstItor->first);
		}

		return (listString);
	}

	// 获得所有属性
	ListString CAttributeManager::GetAllAttribute( void ) const
	{
		ListString listString;

		// 遍历所有的属性
		for (ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.begin(); \
			m_listAttributeFactories.end() != cstItor; ++cstItor)
		{
			listString.push_back(cstItor->first);
		}

		return (listString);
	}

	// 绑定实体属性
	bool CAttributeManager::BindAttribute( IEntityBase* pIEntityBase, const VRString& strFactory )
	{
		// 查询工厂是否存在
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "不存在当前的工厂", ERROR_NOT_FIND);
			return (false);
		}

		// 创建模型属性
		IAttribute* pIAttribute = pIAttributeFactory->CreateInstance(pIEntityBase);
		if (NULL == pIAttribute)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "创建实体失败", ERROR_MALLOC);
			return (false);
		}

		// 添加属性
		pIEntityBase->AddAttributes(pIAttribute);
	/*	IDrawAttribute* pIDrawAttribute = dynamic_cast<IDrawAttribute*>(pIAttribute);
		if (NULL != pIDrawAttribute)
		{
			pIEntityBase->AddDrawAttribute(pIDrawAttribute);
		}
		else
		{
			
		}*/

		// 判断工厂模型是否有值
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

	// 绑定实体属性
	bool CAttributeManager::BindAttribute( IEntityBase* pIEntityBase, IAttribute* pIAttribute )
	{
		// 判断属性是否存在
		if (NULL == pIAttribute)
		{
			return (false);
		}

		if (m_uCurrentID == pIEntityBase->GetID())
		{
			// 添加更新
			for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
				m_vecAttributeUI.end() != cstItor; ++cstItor)
			{
				(*cstItor)->UpdateNewItem(pIAttribute);
			}
		}

		return (true);
	}

	// 接触绑定
	bool CAttributeManager::UnBindAttribute( IEntityBase* pIEntityBase, const VRString& strFactory )
	{
		// 查询工厂是否存在
		IAttributeFactory* pIAttributeFactory = GetFactory(strFactory);
		if (NULL == pIAttributeFactory)
		{
			ILogManager::GetInstance().SetLogMessage(strFactory + "不存在当前的工厂", ERROR_NOT_FIND);
			return (false);
		}

		// 移除属性模型属性
		return (pIEntityBase->RemoveAttribute(strFactory));
	}

	// 解除绑定
	bool CAttributeManager::UnBindAttribute( IEntityBase* pIEntityBase, IAttribute* pIAttribute )
	{
		// 判断是否为空
		if (NULL == pIAttribute)
		{
			return (false);
		}

		if (m_uCurrentID == pIEntityBase->GetID())
		{
			// 添加更新
			for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
				m_vecAttributeUI.end() != cstItor; ++cstItor)
			{
				(*cstItor)->UpdateDelItem(pIAttribute);
			}
		}

		return (true);
	}

	// 获得工厂
	IAttributeFactory* CAttributeManager::GetFactory( const VRString& strFactory ) const
	{
		// 查询是否存在当前的工厂
		ListAttributeFactories::const_iterator cstItor = m_listAttributeFactories.find(strFactory);
		if (m_listAttributeFactories.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);

	}

	// 删除所有的库
	void CAttributeManager::RemoveAllAttributeDll( void )
	{
		// 查询
		for (ListAttributeDlls::iterator itor = m_listAttributeDlls.begin();
			m_listAttributeDlls.end() != itor; ++itor )
		{
			const VRString strDll = itor->first;
			try
			{
				DLL_UNINSTANLL_ATTRIBUTEPLUGIN pDllUnInstanAttri = (DLL_UNINSTANLL_ATTRIBUTEPLUGIN)itor->second->GetSymbol("DllUnInstallAttributePlugin");
				if (NULL == pDllUnInstanAttri)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "属性插件未找到卸载接口DllUnInstallAttributePlugin", ERROR_NOT_FIND);
					return;
				}

				// 加载插件
				pDllUnInstanAttri();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "不是属性插件", ERROR_NOT_COM);
			}

			CDyLibManager::GetInstance().Unload(itor->second);
		}

		m_listAttributeDlls.clear();

	}

	void CAttributeManager::Attach( IAttributeUI* pIAttributeUI )
	{
		m_vecAttributeUI.insert(pIAttributeUI);

		// 获得当前的活动实体是否
		IEntityBase* pICurrentEntity = IEntityManager::GetInstance().GetEntity(m_uCurrentID);
		if (NULL == pICurrentEntity)
		{
			return;
		}

		pIAttributeUI->ChangeEntity(pICurrentEntity);
	}

	// 移除观察者
	void CAttributeManager::Detach( IAttributeUI* pIAttributeUI )
	{
		pIAttributeUI->Clear();

		VctAttributeUI::iterator itor = m_vecAttributeUI.find(pIAttributeUI);
		if (m_vecAttributeUI.end() != itor)
		{
			m_vecAttributeUI.erase(itor);
		}
	}

	// 获得当前激活的实体
	IEntityBase* CAttributeManager::GetCurrentEntityBase( void ) const
	{
		return (IEntityManager::GetInstance().GetEntity(m_uCurrentID));
	}

	// 获得当前激活的实体ID
	uint64_t CAttributeManager::GetCurrentEntityBaseID( void ) const
	{
		return (m_uCurrentID);
	}

	// 初始化
	void CAttributeManager::Init(void)
	{
		// 添加运动属性
		IAttributeFactory* pIAttributeFactory = new CMoveAttributeFactory;
		AddFactory(pIAttributeFactory);

		// 添加实体渲染属性
		pIAttributeFactory = new CEntityDrawAttributeFactory;
		AddFactory(pIAttributeFactory);

		LoadAttributeDll();
	}

	// 移除所有的属性工厂
	void CAttributeManager::RemoveAllFactory( void )
	{
		// 遍历所有的属性工厂
		for (ListAttributeFactories::iterator FactoryItor = m_listAttributeFactories.begin(); m_listAttributeFactories.end() != FactoryItor; ++FactoryItor)
		{
			// 查询添加当前属性的实体
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
			// 获得实体ID
			const ListEntities& listEntities = fcEntities->second;
			std::for_each(listEntities.begin(), listEntities.end(), RmFactory(FactoryItor->first));

			// 从工厂列表中移除
			VRSOFT_DELETE(FactoryItor->second);
		}

		m_listAttributeFactories.clear();
		
	}

}

