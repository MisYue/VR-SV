#include <algorithm>
#include <memory>
#include <osg/Vec3>
#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "AttributeItem.h"

namespace VR_Soft
{
	CAttributeItem::CAttributeItem(IAttribute* pIAttribute,const VRString& strText,const VRString& strUntil, \
		const VRVariant& var)
		:m_bChanged(false),m_bAdded(false),m_strUntil(strUntil), m_pProperty(NULL)
	{
		SetAttribute(pIAttribute);
	}

	CAttributeItem::CAttributeItem(IAttribute* pIAttribute,const VRString& strText, const VRString& strUntil, IProperty* pProperty)
		:m_bChanged(false),m_bAdded(false),m_strUntil(strUntil), m_pProperty(pProperty)
	{
		SetAttribute(pIAttribute);
	}

	CAttributeItem::~CAttributeItem(void)
	{
			
	}

	// 获得值并且采用STring类型表现
	VRString CAttributeItem::GetValueToString(void) const
	{
		VRString str = "";

		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		// 异常捕获
		try
		{ 
			if (NULL == m_pProperty)
			{
				return ("");
			}

			const VRString strType = m_pProperty->GetDataType();
			if (0 == strType.compare(typeid(osg::Vec3d).name()))
			{
				CPropertyType<osg::Vec3d>* pProperty = dynamic_cast<CPropertyType<osg::Vec3d>* >(m_pProperty);
				if (NULL == pProperty)
				{
					return ("");
				}

				osg::Vec3d v = pProperty->GetValue();
				char szTemp[256];
				sprintf(szTemp, "%6f,%6f,%6f", v.x(), v.y(), v.z());
				str = VRString(szTemp);
			}
			else if (0 == strType.compare(typeid(VRString).name()))
			{
				CPropertyType<VRString>* pProperty = dynamic_cast<CPropertyType<VRString>* >(m_pProperty);
				if (NULL == pProperty)
				{
					return ("");
				}

				VRString strValue = pProperty->GetValue();
				str = VRString(strValue);
			}
		}
		
		catch (const boost::bad_any_cast& )
		{
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			str = "";
		}
		

		return (str);
	}

	// 转换成osg::Vec3 类型表现
	osg::Vec3 CAttributeItem::GetValueToVec3(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(osg::Vec3))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (osg::Vec3(0.0f, 0.0f, 0.0f));
		//}

		//osg::Vec3 v = boost::any_cast<osg::Vec3>(m_curCanDidatas.value);
		return (osg::Vec3());
	}

	// 转换成osg::Vec3 类型表现
	osg::Vec3d CAttributeItem::GetValueToVec3d(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(osg::Vec3d))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (osg::Vec3(0.0f, 0.0f, 0.0f));
		//}

		//osg::Vec3d v = boost::any_cast<osg::Vec3d>(m_curCanDidatas.value);
		return (osg::Vec3d());
	}

	// 转换成Int类型
	int CAttributeItem::GetValueToInt(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(int))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//int b = boost::any_cast<int>(m_curCanDidatas.value);
		return (true);
	}

	// 转换成Int类型
	bool CAttributeItem::GetValueToBool(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(bool))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//// 判断是否有待选项
		//bool b = false;
		//if (m_lstCandidata.Empty())
		//{
		//	b = boost::any_cast<bool>(m_curCanDidatas.value);
		//}
		//else
		//{
		//	// 从待选项中选取当前激活的选项
		//	b = boost::any_cast<bool>(m_lstCandidata.GetVariant());
		//}
	
		return (true);
	}

	// 转换成float类型
	// 转换成Int类型
	float CAttributeItem::GetValueToFloat(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		const VRString strType = m_pProperty->GetDataType();
		if (0 == strType.compare(typeid(float).name()))
		{
			CPropertyType<float>* pProperty = dynamic_cast<CPropertyType<float>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (0);
			}

			float fValue = pProperty->GetValue();
			return (fValue);
		}
		else if (0 == strType.compare(typeid(double).name()))
		{
			CPropertyType<double>* pProperty = dynamic_cast<CPropertyType<double>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (0);
			}

			double fValue = pProperty->GetValue();
			return (fValue);
		}
		else if (0 == strType.compare(typeid(int).name()))
		{
			CPropertyType<int>* pProperty = dynamic_cast<CPropertyType<int>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (0);
			}

			int fValue = pProperty->GetValue();
			return (fValue);
		}
		
		//const char* pszTypeName = m_curCanDidatas.value.type().name();
		//if (m_curCanDidatas.value.type() != typeid(float))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//float f = boost::any_cast<float>(m_curCanDidatas.value);
		return (0.0);
	}

	// 转换成Double类型
	double CAttributeItem::GetValueToDobule(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		//const char* pszTypeName = m_curCanDidatas.value.type().name();
		//if (m_curCanDidatas.value.type() != typeid(double))
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//double d = boost::any_cast<double>(m_curCanDidatas.value);
		return (0.0);
	}

	// 设置值 通过设置字符串
	void CAttributeItem::SetValue(const VRVariant& var, bool bUI)
	{
		// 判断是否为
		if (NULL == m_pProperty)
		{
			return;
		}

		std::string str = var.type().name();
		if (var.type() == typeid(float))
		{
			
			float v = boost::any_cast<float>(var);
			if (0 == m_pProperty->GetDataType().compare(var.type().name()))
			{
				CPropertyType<float>* pProperty = dynamic_cast<CPropertyType<float>* >(m_pProperty);
				if (NULL != pProperty)
				{
					pProperty->SetValue(v);
				}
			}
			else if (0 == m_pProperty->GetDataType().compare(typeid(double).name()))
			{
				CPropertyType<double>* pProperty = dynamic_cast<CPropertyType<double>* >(m_pProperty);
				if (NULL != pProperty)
				{
					pProperty->SetValue(v);
				}
			}
			
		}
		else if (var.type() == typeid(double))
		{
			double v = boost::any_cast<double>(var);
			CPropertyType<double>* pProperty = dynamic_cast<CPropertyType<double>* >(m_pProperty);
			if (NULL != pProperty)
			{
				pProperty->SetValue(v);
			}
		}
		else if (var.type() == typeid(osg::Vec3d))
		{
			osg::Vec3d v = boost::any_cast<osg::Vec3d>(var);
			CPropertyType<osg::Vec3d>* pProperty = dynamic_cast<CPropertyType<osg::Vec3d>* >(m_pProperty);
			if (NULL != pProperty)
			{
				pProperty->SetValue(v);
			}
		}
		else if (var.type() == typeid(osg::Vec4d))
		{
			osg::Vec4d v = boost::any_cast<osg::Vec4d>(var);
			CPropertyType<osg::Vec4d>* pProperty = dynamic_cast<CPropertyType<osg::Vec4d>* >(m_pProperty);
			if (NULL != pProperty)
			{
				pProperty->SetValue(v);
			}
		}
		else if (var.type() == typeid(osg::Vec4f))
		{
			osg::Vec4f v = boost::any_cast<osg::Vec4f>(var);
			CPropertyType<osg::Vec4f>* pProperty = dynamic_cast<CPropertyType<osg::Vec4f>* >(m_pProperty);
			if (NULL != pProperty)
			{
				pProperty->SetValue(v);
				return;
			}
			CPropertyType<osg::Vec4d>* pProperty4d = dynamic_cast<CPropertyType<osg::Vec4d>* >(m_pProperty);
			if (NULL != pProperty4d)
			{
				pProperty4d->SetValue(v);
				return;
			}
		}
		else if (var.type() == typeid(VRString) || var.type() == typeid(char*))
		{
			VRString v = "";// boost::any_cast<VRString>(var);
			if (var.type() == typeid(VRString))
			{
				v = boost::any_cast<VRString>(var);
			}
			else
			{
				char * sz = boost::any_cast<char*>(var);
				v = sz;
			}

			// 判断是否为枚举类型
			std::vector<VRString> listStr = m_pProperty->GetEnums();
			if (!listStr.empty())
			{
				m_pProperty->SetSelect(v);
			}
			else
			{	
				CPropertyType<VRString>* pProperty = dynamic_cast<CPropertyType<VRString>* >(m_pProperty);
				if (NULL != pProperty)
				{
					pProperty->SetValue(v);
				}
			}
		}
		

		//// 判断当是否为多个待选项
		//if (!m_lstCandidata.Empty())
		//{
		//	try
		//	{
		//		const char* str = boost::any_cast<const char*>(var);
		//		// 不为空 是否存在 则返回对应的值
		//		bool b;
		//		Candidatas candidata = m_lstCandidata.GetCandidata(str, b);
		//		if (b)
		//		{
		//			m_curCanDidatas = candidata;
		//			m_lstCandidata.SetCandidata(candidata);
		//		}

		//		m_bChanged = true;

		//		// 写入共享内存中
		//		WriteMemory();

		//		// 设置需要更新
		//		GetAttribute()->GetEntity()->NeedUpdate();
		//	}
		//	catch (...)
		//	{
		//		IComManager::GetInstance().WriteLogMsg("当前类型为枚举值", ERRROR_NOT_TYPE);
		//	}

		//	return;
		//}

		//// 判断种类型是否一致
		//if (m_curCanDidatas.value.type() != var.type())
		//{
		//	const char* psz = m_curCanDidatas.value.type().name();
		//	const char* psza = var.type().name();
		//	IComManager::GetInstance().WriteLogMsg("两种类型不一致", ERRROR_NOT_TYPE);
		//	return;
		//}

		//// 正常赋值
		//m_curCanDidatas.value.clear();
		//m_curCanDidatas.value = var;
		//m_bChanged = true;

		//// 更新到共享内存中
		//WriteMemory();

		// 属性值改变
		m_bChanged = true;
		// 设置需要更新
		GetAttribute()->GetEntity()->NeedUpdate();

		if (bUI)
		{
			return;
		}
		// 刷新属性控件
//		IEntityManager::GetInstance().GetAttributeManagerInstance()->UpdateAttributeItem(this);

	}
/*
	TEMEOFDATE XYZ G2000 -> XYZ
		OSG 
*/
	void CAttributeItem::SetValue(const VRString& strCandidata)
	{
		//// 查找是否含有待选项
		m_pProperty->SetSelect(strCandidata);
		//if (m_lstCandidata.Empty())
		//{
		//	SetValue(VRVariant(strCandidata));
		//	return;
		//}

		//// 不为空 是否存在 则返回对应的值
		//bool b;
		//Candidatas candidata = m_lstCandidata.GetCandidata(strCandidata, b);
		//if (b)
		//{
		//	m_curCanDidatas = candidata;
		//}

		//m_bChanged = true;

		//// 写入共享内存中
		//WriteMemory();

		// 设置需要更新
		GetAttribute()->GetEntity()->NeedUpdate();

	}

	std::vector<VRString>  CAttributeItem::GetCandidatas(void) const
	{
		return (m_pProperty->GetEnums());
	}

	// 获得可变参对象
	VRVariant CAttributeItem::GetVariant(void) const
	{
		// 从内存读出
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		/*if (m_lstCandidata.Empty())
		{
			return (m_curCanDidatas.value);
		}
		else
		{
			return (m_lstCandidata.GetVariant());
		}*/
		
		return "";
	}

	// 当前是否改变了属性值
	bool CAttributeItem::IsChanged(void) const
	{
		// 获取第一次改变之后直接设置为不改变（以后有好的方法在进行改进）
		if (m_bChanged)
		{
			m_bChanged = false;
			return (true);
		}
		else
		{
			return (false);
		}
	}

	int CAttributeItem::SelectCandidata(void)
	{
// 		ReadFromMem();
		// 判断是否为
		if (NULL == m_pProperty)
		{
			return (0);
		}

		// 判断是否为枚举类型
		std::vector<VRString> listStr = m_pProperty->GetEnums();
		if (listStr.empty())
		{
			return (0);
		}

		VRString strCur = m_pProperty->GetSelect();
		int nCount = (int)listStr.size();
		for (int index = 0; index < nCount; ++index)
		{
			if (0 == strCur.compare(listStr[index]))
			{
				return (index);
			}
		}


		return (0);
//		return (m_lstCandidata.SelectCandidata());
	}

	void CAttributeItem::SetSelect(const int index)
	{
		//m_lstCandidata.SetSelect(index);

		// 写入内存中
		WriteMemory();

		m_bChanged = true;
	}

	// 保存到内存卡中
	void CAttributeItem::WriteMemory( void ) const
	{
		// 获得内存操作
		IMemoryManager* pIMemManage = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManage)
		{
			return;
		}

		VRString strName = GetTypeName();

		// 获得ID
		uint64_t ID = GetAttribute()->GetEntity()->GetID();
		//// 判断是否为枚举值
		//if (m_lstCandidata.Empty())
		//{
		//	pIMemManage->Write(ID, strName, m_curCanDidatas.value);
		//}
		//else
		//{
		//	// 写入枚举值
		//	pIMemManage->Write(ID, strName, m_lstCandidata.SelectCandidata());
		//}
		
	}

	// 从内存中读取出来
	void CAttributeItem::ReadFromMem( void )
	{
		// 获得内存操作
		IMemoryManager* pIMemManage = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManage)
		{
			return;
		}

		// 获得当前属性名称
		VRString strName = GetTypeName();

		// 获得ID
		uint64_t ID = GetAttribute()->GetEntity()->GetID();

		// 判断是否为枚举值当前选择项
		//if (m_lstCandidata.Empty())
		//{
		//	VRVariant var = pIMemManage->Read(ID, strName, m_curCanDidatas.value.type().name(), m_bChanged);
		//	m_curCanDidatas.value = var.empty()? m_curCanDidatas.value : var;
		//}
		//else
		//{
		//	// 读取枚举值当前选择项
		//	VRVariant var = pIMemManage->Read(ID, strName, "int\0", m_bChanged);
		//	if (var.empty())
		//	{
		//		return;
		//	}
		//	m_lstCandidata.SetSelect(boost::any_cast<int>(var));
		//}
	}

	// 占用空间的大小
	size_t CAttributeItem::GetSize( void ) const
	{
		//// 判断是否为枚举值
		//if (m_lstCandidata.Empty())
		//{
		//	// 如果是字符串
		//	if (typeid(VRString) == m_curCanDidatas.value.type())
		//	{
		//		const VRString& str = boost::any_cast<VRString>(m_curCanDidatas.value);
		//		return (str.size());
		//	}
		//	else if (typeid(osg::Vec3d) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(osg::Vec3d));
		//	}
		//	else if (typeid(osg::Vec3) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(osg::Vec3));
		//	}
		//	else if (typeid(int) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(int));
		//	}
		//	else if (typeid(char) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(char));
		//	}
		//	else if (typeid(bool) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(bool));
		//	}
		//	else if (typeid(float) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(float));
		//	}
		//	else if (typeid(double) == m_curCanDidatas.value.type())
		//	{
		//		return (sizeof(double));
		//	}

		//	return sizeof(m_curCanDidatas.value.type());
		//}
		//else
		//{
		//	// 写入枚举值
		//	return sizeof(int);
		//}

		return (1);
	}

	const VRString& CAttributeItem::GetUntil( void ) const
	{
		return (m_strUntil);
	}

	// 转换成osg::Vec4 类型表现
	osg::Vec4 CAttributeItem::GetValueToVec4( void ) const
	{
		const VRString strType = m_pProperty->GetDataType();
		if (0 == strType.compare(typeid(osg::Vec4).name()))
		{
			CPropertyType<osg::Vec4>* pProperty = dynamic_cast<CPropertyType<osg::Vec4>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (osg::Vec4(0,0,0,1));
			}

			osg::Vec4 fValue = pProperty->GetValue();
			return (fValue);
		}
		else if (0 == strType.compare(typeid(osg::Vec4d).name()))
		{
			CPropertyType<osg::Vec4d>* pProperty = dynamic_cast<CPropertyType<osg::Vec4d>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (osg::Vec4(0,0,0,1));
			}

			osg::Vec4 fValue = pProperty->GetValue();
			return (fValue);
		}

		return (osg::Vec4(0,0,0,1));
	}

	osg::Vec4d CAttributeItem::GetValueToVec4d( void ) const
	{
		const VRString strType = m_pProperty->GetDataType();
		if (0 == strType.compare(typeid(osg::Vec4d).name()))
		{
			CPropertyType<osg::Vec4d>* pProperty = dynamic_cast<CPropertyType<osg::Vec4d>* >(m_pProperty);
			if (NULL == pProperty)
			{
				return (osg::Vec4(0,0,0,1));
			}

			osg::Vec4d fValue = pProperty->GetValue();
			return (fValue);
		}

		return (osg::Vec4d(0,0,0,1));
	}

	// 获得属性接口对象
	IProperty* CAttributeItem::GetProperty( void )
	{
		return (m_pProperty);
	}

}
