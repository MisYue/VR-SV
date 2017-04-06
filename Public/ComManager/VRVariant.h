/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ湲����ϵͳ�ӿ�
 ʱ�䣺 2015-11-03                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _PUBLICE_VRVARIANT_H_
#define _PUBLICE_VRVARIANT_H_

#pragma once

namespace VR_Soft
{
	//��������  
	class IValueBase  
	{  
	public:  
		//virtual type_info GetType()			= 0;
		virtual const char* GetTypeName()   = 0;  
		virtual IValueBase* Clone()         = 0; 
		virtual size_t GetSize(void) const	= 0;
	};  

	//////////////////////////////////////////////////////////////////////////

	//������չΪģ����  
	template<class TypeName>  
	class CValue  : public IValueBase  
	{  
	public:  
		CValue(const TypeName& val)  
			:_value(val)  
		{  

		}  
		/*virtual type_info GetType()
		{
			return (typeid(TypeName));
		}*/
		virtual const char* GetTypeName()  
		{  
			return typeid(TypeName).name();  
		}  
		virtual IValueBase* Clone()  
		{  
			//����һ������  
			return new CValue<TypeName>(_value);  
		}  

		virtual size_t GetSize(void) const	
		{
			// ���ؿռ�Ĵ�С
			return (sizeof(TypeName));
		}
	private:  
		//ģ��������д洢��any����  
		TypeName    _value;  
	};  

	//////////////////////////////////////////////////////////////////////////

	class VRSOFT_DLL CVRVariant
	{
	public:
		CVRVariant(void);
		~CVRVariant(void)
		{
			VRSOFT_DELETE(m_pValue);
		}

		// ���ι���
		template<class T>  
		CVRVariant(const T& t)  
			:m_pValue(new CValue<T>(t))  
		{  

		}  
		//�������캯��  
		CVRVariant(CVRVariant& ma);
		// ��������
		CVRVariant& Swap(CVRVariant& ma) ;
		template<class T>  
		CVRVariant& operator=(const T& val)  
		{  
			//����=�����������ǹ���һ��MyAny����Awap��������ָ���ԭ����Ҫ�ͷŵ��Ǹ�ָ��͵�����ʱ����MyAny(val)��  
			//�������غ���ʱ�����Զ����������������������ͷ�����ڴ棬��������ڴ�й¶��  
			CVRVariant(val).Swap(*this);  
			return *this;  
		}  

		// �Ƿ�Ϊ��
		 bool IsEmpty();
		 // ��õ�ַ�ռ�
		 IValueBase* GetValuePoint(void) const { return m_pValue; }

		 // ת������
		 template<typename ValueType>
		 static ValueType * CVRVariant_Cast(CVRVariant* operand)
		 {
			 return operand && typeid(ValueType).name() == operand->GetValuePoint()->GetTypeName()
				 ? &static_cast<ValueType *>(operand->GetValuePoint())
				 : 0;
		 }
		 const char* GetTypeName() 
		 {
			 return m_pValue->GetTypeName();
		 }
	/*	 type_info GetType()
		 {
			 return (m_pValue->GetType());
		 }*/
		 

	private:  
		//������ָ�룬ָ��һ��������ģ�������  
		IValueBase* m_pValue;  
	};

	// �ɱ��
	// typedef CVRVariant VRVariant;
}


#endif

