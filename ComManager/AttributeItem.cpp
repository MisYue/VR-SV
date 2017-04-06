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

	// ���ֵ���Ҳ���STring���ͱ���
	VRString CAttributeItem::GetValueToString(void) const
	{
		VRString str = "";

		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		// �쳣����
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
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			str = "";
		}
		

		return (str);
	}

	// ת����osg::Vec3 ���ͱ���
	osg::Vec3 CAttributeItem::GetValueToVec3(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(osg::Vec3))
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (osg::Vec3(0.0f, 0.0f, 0.0f));
		//}

		//osg::Vec3 v = boost::any_cast<osg::Vec3>(m_curCanDidatas.value);
		return (osg::Vec3());
	}

	// ת����osg::Vec3 ���ͱ���
	osg::Vec3d CAttributeItem::GetValueToVec3d(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(osg::Vec3d))
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (osg::Vec3(0.0f, 0.0f, 0.0f));
		//}

		//osg::Vec3d v = boost::any_cast<osg::Vec3d>(m_curCanDidatas.value);
		return (osg::Vec3d());
	}

	// ת����Int����
	int CAttributeItem::GetValueToInt(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(int))
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//int b = boost::any_cast<int>(m_curCanDidatas.value);
		return (true);
	}

	// ת����Int����
	bool CAttributeItem::GetValueToBool(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		//if (m_curCanDidatas.value.type() != typeid(bool))
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//// �ж��Ƿ��д�ѡ��
		//bool b = false;
		//if (m_lstCandidata.Empty())
		//{
		//	b = boost::any_cast<bool>(m_curCanDidatas.value);
		//}
		//else
		//{
		//	// �Ӵ�ѡ����ѡȡ��ǰ�����ѡ��
		//	b = boost::any_cast<bool>(m_lstCandidata.GetVariant());
		//}
	
		return (true);
	}

	// ת����float����
	// ת����Int����
	float CAttributeItem::GetValueToFloat(void) const
	{
		// �ӹ����ڴ��ж�ȡ
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
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//float f = boost::any_cast<float>(m_curCanDidatas.value);
		return (0.0);
	}

	// ת����Double����
	double CAttributeItem::GetValueToDobule(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		//const char* pszTypeName = m_curCanDidatas.value.type().name();
		//if (m_curCanDidatas.value.type() != typeid(double))
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
		//	return (false);
		//}

		//double d = boost::any_cast<double>(m_curCanDidatas.value);
		return (0.0);
	}

	// ����ֵ ͨ�������ַ���
	void CAttributeItem::SetValue(const VRVariant& var, bool bUI)
	{
		// �ж��Ƿ�Ϊ
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

			// �ж��Ƿ�Ϊö������
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
		

		//// �жϵ��Ƿ�Ϊ�����ѡ��
		//if (!m_lstCandidata.Empty())
		//{
		//	try
		//	{
		//		const char* str = boost::any_cast<const char*>(var);
		//		// ��Ϊ�� �Ƿ���� �򷵻ض�Ӧ��ֵ
		//		bool b;
		//		Candidatas candidata = m_lstCandidata.GetCandidata(str, b);
		//		if (b)
		//		{
		//			m_curCanDidatas = candidata;
		//			m_lstCandidata.SetCandidata(candidata);
		//		}

		//		m_bChanged = true;

		//		// д�빲���ڴ���
		//		WriteMemory();

		//		// ������Ҫ����
		//		GetAttribute()->GetEntity()->NeedUpdate();
		//	}
		//	catch (...)
		//	{
		//		IComManager::GetInstance().WriteLogMsg("��ǰ����Ϊö��ֵ", ERRROR_NOT_TYPE);
		//	}

		//	return;
		//}

		//// �ж��������Ƿ�һ��
		//if (m_curCanDidatas.value.type() != var.type())
		//{
		//	const char* psz = m_curCanDidatas.value.type().name();
		//	const char* psza = var.type().name();
		//	IComManager::GetInstance().WriteLogMsg("�������Ͳ�һ��", ERRROR_NOT_TYPE);
		//	return;
		//}

		//// ������ֵ
		//m_curCanDidatas.value.clear();
		//m_curCanDidatas.value = var;
		//m_bChanged = true;

		//// ���µ������ڴ���
		//WriteMemory();

		// ����ֵ�ı�
		m_bChanged = true;
		// ������Ҫ����
		GetAttribute()->GetEntity()->NeedUpdate();

		if (bUI)
		{
			return;
		}
		// ˢ�����Կؼ�
//		IEntityManager::GetInstance().GetAttributeManagerInstance()->UpdateAttributeItem(this);

	}
/*
	TEMEOFDATE XYZ G2000 -> XYZ
		OSG 
*/
	void CAttributeItem::SetValue(const VRString& strCandidata)
	{
		//// �����Ƿ��д�ѡ��
		m_pProperty->SetSelect(strCandidata);
		//if (m_lstCandidata.Empty())
		//{
		//	SetValue(VRVariant(strCandidata));
		//	return;
		//}

		//// ��Ϊ�� �Ƿ���� �򷵻ض�Ӧ��ֵ
		//bool b;
		//Candidatas candidata = m_lstCandidata.GetCandidata(strCandidata, b);
		//if (b)
		//{
		//	m_curCanDidatas = candidata;
		//}

		//m_bChanged = true;

		//// д�빲���ڴ���
		//WriteMemory();

		// ������Ҫ����
		GetAttribute()->GetEntity()->NeedUpdate();

	}

	std::vector<VRString>  CAttributeItem::GetCandidatas(void) const
	{
		return (m_pProperty->GetEnums());
	}

	// ��ÿɱ�ζ���
	VRVariant CAttributeItem::GetVariant(void) const
	{
		// ���ڴ����
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

	// ��ǰ�Ƿ�ı�������ֵ
	bool CAttributeItem::IsChanged(void) const
	{
		// ��ȡ��һ�θı�֮��ֱ������Ϊ���ı䣨�Ժ��кõķ����ڽ��иĽ���
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
		// �ж��Ƿ�Ϊ
		if (NULL == m_pProperty)
		{
			return (0);
		}

		// �ж��Ƿ�Ϊö������
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

		// д���ڴ���
		WriteMemory();

		m_bChanged = true;
	}

	// ���浽�ڴ濨��
	void CAttributeItem::WriteMemory( void ) const
	{
		// ����ڴ����
		IMemoryManager* pIMemManage = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManage)
		{
			return;
		}

		VRString strName = GetTypeName();

		// ���ID
		uint64_t ID = GetAttribute()->GetEntity()->GetID();
		//// �ж��Ƿ�Ϊö��ֵ
		//if (m_lstCandidata.Empty())
		//{
		//	pIMemManage->Write(ID, strName, m_curCanDidatas.value);
		//}
		//else
		//{
		//	// д��ö��ֵ
		//	pIMemManage->Write(ID, strName, m_lstCandidata.SelectCandidata());
		//}
		
	}

	// ���ڴ��ж�ȡ����
	void CAttributeItem::ReadFromMem( void )
	{
		// ����ڴ����
		IMemoryManager* pIMemManage = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManage)
		{
			return;
		}

		// ��õ�ǰ��������
		VRString strName = GetTypeName();

		// ���ID
		uint64_t ID = GetAttribute()->GetEntity()->GetID();

		// �ж��Ƿ�Ϊö��ֵ��ǰѡ����
		//if (m_lstCandidata.Empty())
		//{
		//	VRVariant var = pIMemManage->Read(ID, strName, m_curCanDidatas.value.type().name(), m_bChanged);
		//	m_curCanDidatas.value = var.empty()? m_curCanDidatas.value : var;
		//}
		//else
		//{
		//	// ��ȡö��ֵ��ǰѡ����
		//	VRVariant var = pIMemManage->Read(ID, strName, "int\0", m_bChanged);
		//	if (var.empty())
		//	{
		//		return;
		//	}
		//	m_lstCandidata.SetSelect(boost::any_cast<int>(var));
		//}
	}

	// ռ�ÿռ�Ĵ�С
	size_t CAttributeItem::GetSize( void ) const
	{
		//// �ж��Ƿ�Ϊö��ֵ
		//if (m_lstCandidata.Empty())
		//{
		//	// ������ַ���
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
		//	// д��ö��ֵ
		//	return sizeof(int);
		//}

		return (1);
	}

	const VRString& CAttributeItem::GetUntil( void ) const
	{
		return (m_strUntil);
	}

	// ת����osg::Vec4 ���ͱ���
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

	// ������Խӿڶ���
	IProperty* CAttributeItem::GetProperty( void )
	{
		return (m_pProperty);
	}

}
