/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���Բ��ͷ�ļ�		                                        */
/* ʱ�䣺 2016-06-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ATTRIBUTEPLUGIN_H_
#define _PUBLIC_ATTRIBUTEPLUGIN_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeFactory
	{
	public:
		// ��������
		virtual ~IAttributeFactory(void) { }
		// �������
		virtual const VRString& GetName(void) const = 0;
		// ����ʵ��
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