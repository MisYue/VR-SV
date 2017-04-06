#ifndef _ICOMFACTORY_H
#define _ICOMFACTORY_H


namespace VR_Soft
{
	class IComManagerFace;

	typedef struct ComManagerMetaData_TYP
	{
		VRString strType;
		VRString strInstanceName;
		VRString strDescription;
	}ComManagerMetaData, *PTR_ComManagerMetaData;

	class VRSOFT_DLL IComFactory
	{
	public:
		//	ETZ	m_bMetaDataInit�޳�ֵ
		IComFactory():m_bMetaDataInit(true){}
		// ��������
		virtual ~IComFactory() { }
		// ����ʵ��
		virtual IComManagerFace* CreateInstance(const VRString& strInstaneName) = 0;
		// ����ʵ��
		virtual void DestoryInstance(IComManagerFace* pInstance) = 0;
		// ��ʼ��
		virtual void InitMetaData(void) const = 0;
		// ��ȡ����
		virtual const ComManagerMetaData& GetMetaData(void) const
		{
			if (m_bMetaDataInit)
			{
				InitMetaData();
				m_bMetaDataInit = false;
			}
			return m_MetaDate;
		}

	protected:
		mutable ComManagerMetaData m_MetaDate;
		mutable bool m_bMetaDataInit;
	};

	// ���幤����
#define REGISTER_COMFACTORY(classname, factoryname, stypename, instancename, sDesc) \
	class C##factoryname##Factory : public IComFactory{\
	public:\
		virtual ~C##factoryname##Factory() { }\
		virtual IComManagerFace* CreateInstance(const VRString& strInstaneName ){return (new classname(strInstaneName));}\
		virtual void DestoryInstance(IComManagerFace* pInstance){delete pInstance;}\
		virtual void InitMetaData(void) const {m_MetaDate.strType=stypename; m_MetaDate.strInstanceName=instancename; m_MetaDate.strDescription=sDesc;} \
	public:\
		static const VRString FACTORY_TYPE_NAME;};\

}

#endif // _ICOMFACTORY_H