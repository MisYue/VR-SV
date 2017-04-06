/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体管理类			                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IENTITYCOMPONENT_H_
#define _IENTITYCOMPONENT_H_

namespace VR_Soft
{
	class IEntityBase;
	class IEntityBaseFactory;

	class VRSOFT_DLL IEntityComponent 
	{
	public:
		// 构造函数
		explicit IEntityComponent(): m_strName(""), m_strPath(""), m_pParentEntity(NULL)
		{
		}
		// 析构函数
		virtual ~IEntityComponent() 
		{
		}
		// 设置名称
		virtual void SetName(const VRString& strName) 
		{
			m_strName = strName;
		}

		// 获得名称
		virtual VRString GetName(void) const
		{
			return (m_strName);
		}

		// 设置路径
		virtual void SetPath(const VRString& strPath) { m_strPath = strPath; }
		// 获得路径
		virtual VRString GetPath(void) const { return (m_strPath); }
		// 设置父对象
		virtual void SetParentEntity(IEntityComponent* pIEntityManager) { m_pParentEntity = pIEntityManager; }
		// 获得父对象
		virtual IEntityComponent* GetParentEntity(void) { return (m_pParentEntity); }
		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt) { }
		// 是否含有子集
		virtual bool IsExport(void) { return (false); }

	protected:
		VRString m_strName; // 名称
		VRString m_strPath; // 路径 防止添加形成环路
		IEntityComponent* m_pParentEntity; // 父对象
	};
}

#endif // _IENTITYCOMPONENT_H_