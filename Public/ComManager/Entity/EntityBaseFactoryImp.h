/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����๤����ģ��	                                        */
/* ʱ�䣺 2015-05-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENTITYBASEFACTORYIMP_H_
#define _ENTITYBASEFACTORYIMP_H_

namespace VR_Soft
{
	template<class T>
	class CEntityBaseFactoryImp : public IEntityBaseFactory
	{
	public:
		// ���캯��
		explicit CEntityBaseFactoryImp(const VRString& strType);
		// ��������
		virtual ~CEntityBaseFactoryImp(void);
	public:
		// ��ȡ����
		virtual VRString GetEntiryBaseType(void) const;
		// ��������
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

	// ��ȡ����
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

	// ע��ʵ����������
#define REGISTER_BASEENTITY_FACTORY(classname, basetype) \
	class classname##Factory : public CEntityBaseFactoryImp<classname##Factory>\
	{\
	public:\
		explicit classname##Factory(const VRString& strType = basetype):CEntityBaseFactoryImp<classname##Factory>(strType) { } \
		virtual IEntityBulider* CreateEntityBuilder(void) { IEntityBulider* pIEntityBulider = new classname; return (pIEntityBulider); } \
	};

	// ʵ����������
#define CREATE_BASEENTITY_FACTORY(classname) (new classname##Factory)
}

#endif //  _ENTITYBASEFACTORYIMP_H_