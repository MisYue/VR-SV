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

	// 获得值并且采用STring类型表现
	VRString CAttributeItem::GetValueToString(void) const
	{
		VRString str = "";

		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		// 异常捕获
		try
		{ 
			// 判断类型是否为整数  
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
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			str = "";
		}
		

		return (str);
	}

	// 转换成osg::Vec3 类型表现
	osg::Vec3 CAttributeItem::GetValueToVec3(void)
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(osg::Vec3))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (osg::Vec3(0.0f, 0.0f, 0.0f));
		}

		osg::Vec3 v = boost::any_cast<osg::Vec3>(m_curCanDidatas.value);
		return (v);
	}

	// 转换成osg::Vec3 类型表现
	osg::Vec3d CAttributeItem::GetValueToVec3d(void)
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(osg::Vec3d))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (osg::Vec3(0.0f, 0.0f, 0.0f));
		}

		osg::Vec3d v = boost::any_cast<osg::Vec3d>(m_curCanDidatas.value);
		return (v);
	}

	// 转换成Int类型
	int CAttributeItem::GetValueToInt(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(int))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (false);
		}

		int b = boost::any_cast<int>(m_curCanDidatas.value);
		return (b);
	}

	// 转换成Int类型
	bool CAttributeItem::GetValueToBool(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();

		if (m_curCanDidatas.value.type() != typeid(bool))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (false);
		}

		// 判断是否有待选项
		bool b = false;
		if (m_lstCandidata.Empty())
		{
			b = boost::any_cast<bool>(m_curCanDidatas.value);
		}
		else
		{
			// 从待选项中选取当前激活的选项
			b = boost::any_cast<bool>(m_lstCandidata.GetVariant());
		}
	
		return (b);
	}

	// 转换成float类型
	// 转换成Int类型
	float CAttributeItem::GetValueToFloat(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		const char* pszTypeName = m_curCanDidatas.value.type().name();
		if (m_curCanDidatas.value.type() != typeid(float))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (false);
		}

		float f = boost::any_cast<float>(m_curCanDidatas.value);
		return (f);
	}

	// 转换成Double类型
	double CAttributeItem::GetValueToDobule(void) const
	{
		// 从共享内存中读取
		(const_cast<CAttributeItem*>(this))->ReadFromMem();
		const char* pszTypeName = m_curCanDidatas.value.type().name();
		if (m_curCanDidatas.value.type() != typeid(double))
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("类型转换失败", ERROR_CONVER_FAILD);
			return (false);
		}

		double d = boost::any_cast<double>(m_curCanDidatas.value);
		return (d);
	}

	// 设置值 通过设置字符串
	void CAttributeItem::SetValue(const VRVariant& var, bool bUI)
	{
		// 判断种类型是否一致
		if (m_curCanDidatas.value.type() != var.type())
		{
			const char* psz = m_curCanDidatas.value.type().name();
			const char* psza = var.type().name();
			IComManager::GetInstance().WriteLogMsg("两种类型不一致", ERRROR_NOT_TYPE);
			return;
		}

		// 正常赋值
		m_curCanDidatas.value.clear();
		m_curCanDidatas.value = var;
		m_bChanged = true;

		// 更新到共享内存中
		WriteMemory();

		if (bUI)
		{
			return;
		}
		// 刷新属性控件
		IEntityManager::GetInstance().GetAttributeManagerInstance()->UpdateAttributeItem(this);

	}
/*
	TEMEOFDATE XYZ G2000 -> XYZ
		OSG 
*/
	void CAttributeItem::SetValue(const VRString& strCandidata)
	{
		// 查找是否含有待选项
		if (m_lstCandidata.Empty())
		{
			SetValue(VRVariant(strCandidata));
			return;
		}

		// 不为空 是否存在 则返回对应的值
		bool b;
		Candidatas candidata = m_lstCandidata.GetCandidata(strCandidata, b);
		if (b)
		{
			m_curCanDidatas = candidata;
		}

		m_bChanged = true;

		// 写入共享内存中
		WriteMemory();

	}

	// 添加待选项
	void CAttributeItem::AddCandidatas(const VRString& strText, const VRVariant& value, bool bSelect)
	{
		// 确保线程安全
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

	// 获得可变参对象
	VRVariant CAttributeItem::GetVariant(void) const
	{
		// 从内存读出
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
		ReadFromMem();
		return (m_lstCandidata.SelectCandidata());
	}

	void CAttributeItem::SetSelect(const int index)
	{
		m_lstCandidata.SetSelect(index);

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
		// 判断是否为枚举值
		if (m_lstCandidata.Empty())
		{
			pIMemManage->Write(ID, strName, m_curCanDidatas.value);
		}
		else
		{
			// 写入枚举值
			pIMemManage->Write(ID, strName, m_lstCandidata.SelectCandidata());
		}
		
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
		if (m_lstCandidata.Empty())
		{
			VRVariant var = pIMemManage->Read(ID, strName, m_curCanDidatas.value.type().name(), m_bChanged);
			m_curCanDidatas.value = var.empty()? m_curCanDidatas.value : var;
		}
		else
		{
			// 读取枚举值当前选择项
			VRVariant var = pIMemManage->Read(ID, strName, "int\0", m_bChanged);
			if (var.empty())
			{
				return;
			}
			m_lstCandidata.SetSelect(boost::any_cast<int>(var));
		}
	}

	// 占用空间的大小
	size_t CAttributeItem::GetSize( void ) const
	{
		// 判断是否为枚举值
		if (m_lstCandidata.Empty())
		{
			// 如果是字符串
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
			// 写入枚举值
			return sizeof(int);
		}
	}

	const VRString& CAttributeItem::GetUntil( void ) const
	{
		return (m_strUntil);
	}

}
