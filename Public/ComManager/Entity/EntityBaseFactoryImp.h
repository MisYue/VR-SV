/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类工厂类模板	                                        */
/* 时间： 2015-05-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENTITYBASEFACTORYIMP_H_
#define _ENTITYBASEFACTORYIMP_H_

namespace VR_Soft
{
	template<class T>
	class CEntityBaseFactoryImp : public IEntityBaseFactory
	{
	public:
		// 构造函数
		explicit CEntityBaseFactoryImp(const VRString& strType);
		// 析构函数
		virtual ~CEntityBaseFactoryImp(void);
	public:
		// 获取类型
		virtual VRString GetEntiryBaseType(void) const;
		// 创建类型
		virtual IEntityBulider* CreateEntityBuilder(void);

	private:
		int m_nCount ;
		VRString m_strEntityType;
	};

	template <class T>
	CEntityBaseFactoryImp<T>::CEntityBaseFactoryImp(const VRString& strType):m_nCount(0), m_strEntityType(strType)
	{

	}

	template <class T>
	CEntityBaseFactoryImp<T>::~CEntityBaseFactoryImp()
	{

	}

	// 获取类型
	template <class T>
	VRString CEntityBaseFactoryImp<T>::GetEntiryBaseType(void) const
	{
		return m_strEntityType;
	}

	template <class T>
	IEntityBulider* CEntityBaseFactoryImp<T>::CreateEntityBuilder()
	{
		return (NULL);
	}

	// 注册实例化工厂宏
#define REGISTER_BASEENTITY_FACTORY(classname, basetype) \
	class classname##Factory : public CEntityBaseFactoryImp<classname##Factory>\
	{\
	public:\
		explicit classname##Factory(const VRString& strType = basetype):CEntityBaseFactoryImp<classname##Factory>(strType) { } \
		virtual IEntityBulider* CreateEntityBuilder(void) { IEntityBulider* pIEntityBulider = new classname; return (pIEntityBulider); } \
	};

	// 实例化工厂宏
#define CREATE_BASEENTITY_FACTORY(classname) (new classname##Factory)
}

#endif //  _ENTITYBASEFACTORYIMP_H_