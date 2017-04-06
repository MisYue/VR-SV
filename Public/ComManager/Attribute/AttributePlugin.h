/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  属性插件头文件		                                        */
/* 时间： 2016-06-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ATTRIBUTEPLUGIN_H_
#define _PUBLIC_ATTRIBUTEPLUGIN_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeFactory
	{
	public:
		// 析构函数
		virtual ~IAttributeFactory(void) { }
		// 获得名称
		virtual const VRString& GetName(void) const = 0;
		// 创建实体
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) = 0;
	};

#define DEFINED_ATTRIBUTEFACTORY(ATTRIBUTE_DLL, CLASSNAME, ATTRIBUTENAME, BDRAW)					\
	class ATTRIBUTE_DLL CLASSNAME##Factory : public IAttributeFactory								\
	{																								\
	public:																							\
	CLASSNAME##Factory(void):m_strAttributeName(ATTRIBUTENAME) { }									\
	virtual ~CLASSNAME##Factory(void) { }															\
	virtual const VRString& GetName(void) const { return (m_strAttributeName); }					\
	virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CLASSNAME(pIEntity)); }	\
	private:																						\
	VRString m_strAttributeName;																	\
	};																								\
	EXTERN_CPP ATTRIBUTE_DLL void DllInstallAttributePlugin(void)									\
	{																								\
	IAttributeFactory* pIAttributeFactory = new CLASSNAME##Factory;									\
	IAttributeManager::GetInstance().AddFactory(pIAttributeFactory);									\
	}																								\
	EXTERN_CPP ATTRIBUTE_DLL void DllUnInstallAttributePlugin(void)									\
	{																								\
	IAttributeManager::GetInstance().RemoveFactory(ATTRIBUTENAME);										\
	}	
}

#endif // !_PUBLIC_ATTRIBUTEPLUGIN_H_