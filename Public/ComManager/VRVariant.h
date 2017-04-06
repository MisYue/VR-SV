/************************************************************************
 作者： LJ                                                            
 用途:  内存共享插件系统接口
 时间： 2015-11-03                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _PUBLICE_VRVARIANT_H_
#define _PUBLICE_VRVARIANT_H_

#pragma once

namespace VR_Soft
{
	//基类声明  
	class IValueBase  
	{  
	public:  
		//virtual type_info GetType()			= 0;
		virtual const char* GetTypeName()   = 0;  
		virtual IValueBase* Clone()         = 0; 
		virtual size_t GetSize(void) const	= 0;
	};  

	//////////////////////////////////////////////////////////////////////////

	//子类扩展为模板类  
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
			//拷贝一份数据  
			return new CValue<TypeName>(_value);  
		}  

		virtual size_t GetSize(void) const	
		{
			// 返回空间的大小
			return (sizeof(TypeName));
		}
	private:  
		//模板类对象中存储着any数据  
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

		// 带参构造
		template<class T>  
		CVRVariant(const T& t)  
			:m_pValue(new CValue<T>(t))  
		{  

		}  
		//拷贝构造函数  
		CVRVariant(CVRVariant& ma);
		// 交换函数
		CVRVariant& Swap(CVRVariant& ma) ;
		template<class T>  
		CVRVariant& operator=(const T& val)  
		{  
			//重载=操作符，先是构造一个MyAny对象，Awap交换对象指针后，原来需要释放的那个指针就到了临时对象MyAny(val)中  
			//函数返回后，临时变量自动析构，调用了析构函数释放这块内存，不会造成内存泄露。  
			CVRVariant(val).Swap(*this);  
			return *this;  
		}  

		// 是否为空
		 bool IsEmpty();
		 // 获得地址空间
		 IValueBase* GetValuePoint(void) const { return m_pValue; }

		 // 转换函数
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
		//虚基类的指针，指向一个派生的模板类对象  
		IValueBase* m_pValue;  
	};

	// 可变参
	// typedef CVRVariant VRVariant;
}


#endif

