#define VRSOFT_PLUGIN_EXPORT
#include <algorithm>
#include <memory>
#include <osg/Vec3>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/IAttributeItem.h"
#include "../../Public/EntitySystem/AttributeImp.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "AttributeItem.h"

namespace VR_Soft
{
	CAttributeItem::CAttributeItem(IAttribute* pIAttribute,const VRString& strText,const VRString& strUntil, \
		const VRVariant& var)
		:m_curCanDidatas(strText,var, true),m_bChanged(false),m_bAdded(false),m_strUntil(strUntil)
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
			// �ж������Ƿ�Ϊ����  
			if (typeid(int) == m_curCanDidatas.value.type())
			{
				int nVar = boost::any_cast<int>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%d", nVar);
				str = VRString(szTemp);

			}
			else if (typeid(float) == m_curCanDidatas.value.type())
			{
				float fVar = boost::any_cast<float>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%f", fVar);
				str = VRString(szTemp);
			}
			else if (typeid(double) == m_curCanDidatas.value.type())
			{
				double dVar = boost::any_cast<double>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%f", dVar);
				str = VRString(szTemp);
			}
			else if (typeid(VRString) == m_curCanDidatas.value.type())
			{
				str = boost::any_cast<VRString>(m_curCanDidatas.value);
			}
			else if (typeid(bool) == m_curCanDidatas.value.type())
			{
				bool b = boost::any_cast<bool>(m_curCanDidatas.value);
				str = b ? "true" : "false";
			}
			else if (typeid(osg::Vec3) == m_curCanDidatas.value.type())
			{
				osg::Vec3 v = boost::any_cast<osg::Vec3>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%f,%f,%f", v.x(), v.y(), v.z());
				str = VRString(szTemp);
			}
			else if (typeid(osg::Vec3d) == m_curCanDidatas.value.type())
			{
				osg::Vec3d v = boost::any_cast<osg::Vec3d>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%6f,%6f,%6f", v.x(), v.y(), v.z());
				str = VRString(szTemp);
			}
			else if (typeid(osg::Vec4) == m_curCanDidatas.value.type())
			{
				osg::Vec4 v = boost::any_cast<osg::Vec4>(m_curCanDidatas.value);
				char szTemp[256];
				sprintf(szTemp, "%f,%f,%f,%f", v.r(), v.g(), v.b(), v.a());
				str = VRString(szTemp);
			}
			else if (!m_lstCandidata.Empty())
			{
				char szTemp[256];
				sprintf(szTemp, "%d", m_lstCandidata.SelectCandidata());
				str = VRString(szTemp);
				return (str);
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
	osg::Vec3 CAttributeItem::GetValueToVec3(void)
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(osg::Vec3))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (osg::Vec3(0.0f, 0.0f, 0.0f));
		}

		osg::Vec3 v = boost::any_cast<osg::Vec3>(m_curCanDidatas.value);
		return (v);
	}

	// ת����osg::Vec3 ���ͱ���
	osg::Vec3d CAttributeItem::GetValueToVec3d(void)
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(osg::Vec3d))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (osg::Vec3(0.0f, 0.0f, 0.0f));
		}

		osg::Vec3d v = boost::any_cast<osg::Vec3d>(m_curCanDidatas.value);
		return (v);
	}

	// ת����Int����
	int CAttributeItem::GetValueToInt(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(int))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (false);
		}

		int b = boost::any_cast<int>(m_curCanDidatas.value);
		return (b);
	}

	// ת����Int����
	bool CAttributeItem::GetValueToBool(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(bool))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (false);
		}

		// �ж��Ƿ��д�ѡ��
		bool b = false;
		if (m_lstCandidata.Empty())
		{
			b = boost::any_cast<bool>(m_curCanDidatas.value);
		}
		else
		{
			// �Ӵ�ѡ����ѡȡ��ǰ�����ѡ��
			b = boost::any_cast<bool>(m_lstCandidata.GetVariant());
		}
	
		return (b);
	}

	// ת����float����
	// ת����Int����
	float CAttributeItem::GetValueToFloat(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		const char* pszTypeName = m_curCanDidatas.value.type().name();
		if (m_curCanDidatas.value.type() != typeid(float))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (false);
		}

		float f = boost::any_cast<float>(m_curCanDidatas.value);
		return (f);
	}

	// ת����Double����
	double CAttributeItem::GetValueToDobule(void) const
	{
		// �ӹ����ڴ��ж�ȡ
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		const char* pszTypeName = m_curCanDidatas.value.type().name();
		if (m_curCanDidatas.value.type() != typeid(double))
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("����ת��ʧ��", ERROR_CONVER_FAILD);
			return (false);
		}

		double d = boost::any_cast<double>(m_curCanDidatas.value);
		return (d);
	}

	// ����ֵ ͨ�������ַ���
	void CAttributeItem::SetValue(const VRVariant& var, bool bUI)
	{
		// �ж��������Ƿ�һ��
		if (m_curCanDidatas.value.type() != var.type())
		{
			const char* psz = m_curCanDidatas.value.type().name();
			const char* psza = var.type().name();
			IComManager::GetInstance().WriteLogMsg("�������Ͳ�һ��", ERRROR_NOT_TYPE);
			return;
		}

		// ������ֵ
		m_curCanDidatas.value.clear();
		m_curCanDidatas.value = var;
		m_bChanged = true;

		// ���µ������ڴ���
		WriteMemory();

		if (bUI)
		{
			return;
		}
		// ˢ�����Կؼ�
		IEntityManager::GetInstance().GetAttributeManagerInstance()->UpdateAttributeItem(this);

	}
/*
	TEMEOFDATE XYZ G2000 -> XYZ
		OSG 
*/
	void CAttributeItem::SetValue(const VRString& strCandidata)
	{
		// �����Ƿ��д�ѡ��
		if (m_lstCandidata.Empty())
		{
			SetValue(VRVariant(strCandidata));
			return;
		}

		// ��Ϊ�� �Ƿ���� �򷵻ض�Ӧ��ֵ
		bool b;
		Candidatas candidata = m_lstCandidata.GetCandidata(strCandidata, b);
		if (b)
		{
			m_curCanDidatas = candidata;
		}

		m_bChanged = true;

		// д�빲���ڴ���
		WriteMemory();

	}

	// ��Ӵ�ѡ��
	void CAttributeItem::AddCandidatas(const VRString& strText, const VRVariant& value, bool bSelect)
	{
		// ȷ���̰߳�ȫ
		VR_MUTEX_AUTO;

		if (!m_bAdded)
		{
			m_lstCandidata.Add(m_curCanDidatas);
			m_bAdded = true;
		}

		m_lstCandidata.Add(Candidatas(strText, value, bSelect));
	}

	const IAttributeItem::LstCandidatas& CAttributeItem::GetCandidatas(void) const
	{
		return (m_lstCandidata.GetCandidatas());
	}

	// ��ÿɱ�ζ���
	VRVariant CAttributeItem::GetVariant(void) const
	{
		// ���ڴ����
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		if (m_lstCandidata.Empty())
		{
			return (m_curCanDidatas.value);
		}
		else
		{
			return (m_lstCandidata.GetVariant());
		}
		
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
		ReadFromMem();
		return (m_lstCandidata.SelectCandidata());
	}

	void CAttributeItem::SetSelect(const int index)
	{
		m_lstCandidata.SetSelect(index);

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
		// �ж��Ƿ�Ϊö��ֵ
		if (m_lstCandidata.Empty())
		{
			pIMemManage->Write(ID, strName, m_curCanDidatas.value);
		}
		else
		{
			// д��ö��ֵ
			pIMemManage->Write(ID, strName, m_lstCandidata.SelectCandidata());
		}
		
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
		if (m_lstCandidata.Empty())
		{
			VRVariant var = pIMemManage->Read(ID, strName, m_curCanDidatas.value.type().name(), m_bChanged);
			m_curCanDidatas.value = var.empty()? m_curCanDidatas.value : var;
		}
		else
		{
			// ��ȡö��ֵ��ǰѡ����
			VRVariant var = pIMemManage->Read(ID, strName, "int\0", m_bChanged);
			if (var.empty())
			{
				return;
			}
			m_lstCandidata.SetSelect(boost::any_cast<int>(var));
		}
	}

	// ռ�ÿռ�Ĵ�С
	size_t CAttributeItem::GetSize( void ) const
	{
		// �ж��Ƿ�Ϊö��ֵ
		if (m_lstCandidata.Empty())
		{
			// ������ַ���
			if (typeid(VRString) == m_curCanDidatas.value.type())
			{
				const VRString& str = boost::any_cast<VRString>(m_curCanDidatas.value);
				return (str.size());
			}
			else if (typeid(osg::Vec3d) == m_curCanDidatas.value.type())
			{
				return (sizeof(osg::Vec3d));
			}
			else if (typeid(osg::Vec3) == m_curCanDidatas.value.type())
			{
				return (sizeof(osg::Vec3));
			}
			else if (typeid(int) == m_curCanDidatas.value.type())
			{
				return (sizeof(int));
			}
			else if (typeid(char) == m_curCanDidatas.value.type())
			{
				return (sizeof(char));
			}
			else if (typeid(bool) == m_curCanDidatas.value.type())
			{
				return (sizeof(bool));
			}
			else if (typeid(float) == m_curCanDidatas.value.type())
			{
				return (sizeof(float));
			}
			else if (typeid(double) == m_curCanDidatas.value.type())
			{
				return (sizeof(double));
			}

			return sizeof(m_curCanDidatas.value.type());
		}
		else
		{
			// д��ö��ֵ
			return sizeof(int);
		}
	}

	const VRString& CAttributeItem::GetUntil( void ) const
	{
		return (m_strUntil);
	}

}
