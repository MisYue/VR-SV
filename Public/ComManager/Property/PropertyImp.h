/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性模板类		                                        */
/* 时间： 2016-05-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_PROPERTYIMP_H_
#define _PUBLIC_PROPERTYIMP_H_

#include <functional>

namespace VR_Soft
{
	class VRSOFT_DLL IProperty
	{
	public: 
		virtual ~IProperty(void) { }
		virtual VRString GetDataType(void) = 0;
		virtual void SetSelect(VRString strName) = 0;
		virtual VRString GetSelect(void) = 0;
		virtual std::vector<VRString> GetEnums(void) = 0;
	};

	template <typename ValueType>
	class CPropertyType : public IProperty
	{
	public:
		virtual ~CPropertyType(void) { }
		virtual ValueType GetValue(void) = 0;
		virtual void SetValue(ValueType value) = 0;
		virtual void AddEnum(VRString strName, ValueType value) = 0;
		
	};

	template<typename Container, typename ValueType>
	class CProperty : public CPropertyType<ValueType>
	{
	public:
		CProperty(void)
		{
			m_cObject = NULL;
			ConstRefSet = NULL;
			ConstSet = NULL;
			Set = NULL;

			ConstRefGet = NULL;
			ConstGet = NULL;
			Get = NULL;
		}

		virtual ~CProperty(void) { }

		virtual VRString GetDataType(void) 
		{
			return (typeid(ValueType).name());
		}

		virtual ValueType GetValue(void) 
		{
			assert(m_cObject != NULL);
			// assert(Get != NULL);

			if (NULL != ConstRefGet)
			{
				return ((m_cObject->*ConstRefGet)());
			}
			else if (NULL != ConstGet)
			{
				return ((m_cObject->*ConstGet)());
			}
			else if (NULL != Get)
			{
				return ((m_cObject->*Get)());
			}

			return (ValueType());
		}

		virtual void SetValue(ValueType value)
		{
			assert(m_cObject != NULL);

			if (NULL != ConstRefSet)
			{
				(m_cObject->*ConstRefSet)(value);
			}
			else if (NULL != ConstSet)
			{
				(m_cObject->*ConstSet)(value);
			}
			else if (NULL != Set)
			{
				(m_cObject->*Set)(value);
			}
		}

		// 设置容器
		void setContainer(Container* cObject)
		{
			m_cObject = cObject;
		}
		
		// 设置设置器
		void setter(void (Container::*pSet)(const ValueType& value))
		{
			ConstRefSet = pSet;
		}

		// 设置设置器
		void setter(void (Container::*pSet)(const ValueType value))
		{
			ConstSet = pSet;
		}
		
		//// 设置设置器
		//void setter(void (Container::*pSet)(ValueType value))
		//{
		//	Set = pSet;
		//}
		
		// 设置访问器
		void getter(ValueType& (Container::*pGet)() const)
		{
			ConstRefGet = pGet;
		}

		// 设置访问器
		void getter(ValueType (Container::*pGet)() const)
		{
			ConstGet = pGet;
		}

		// 设置访问器
		void getter(ValueType (Container::*pGet)())
		{
			Get = pGet;
		}
		
		ValueType operator =(const ValueType& value)
		{
			assert(m_cObject != NULL);

			if (NULL != ConstRefSet)
			{
				(m_cObject->*ConstRefSet)(value);
			}
			else if (NULL != ConstSet)
			{
				(m_cObject->*ConstSet)(value);
			}
			else if (NULL != Set)
			{
				(m_cObject->*Set)(value);
			}
			
			return value;
		}

		
		operator ValueType()
		{
			assert(m_cObject != NULL);
			// assert(Get != NULL);

			if (NULL != ConstRefGet)
			{
				return ((m_cObject->*ConstRefGet)());
			}
			else if (NULL != ConstGet)
			{
				return ((m_cObject->*ConstGet)());
			}
			else if (NULL != Get)
			{
				return ((m_cObject->*Get)());
			}
		
		}

		virtual void AddEnum(VRString strName, ValueType value) 
		{
			m_strSelect = m_strSelect;
			m_listValueType.push_back(EnumType<ValueType>(strName, value));
		}

		virtual void SetSelect(VRString strName) 
		{
			std::vector<EnumType<ValueType> >::iterator itor = std::find(m_listValueType.begin(), m_listValueType.end(), strName);
			if (m_listValueType.end() == itor)
			{
				return;
			}

			m_strSelect = strName;
			SetValue(itor->m_valueType);
		}

		virtual VRString GetSelect(void)
		{
			return (m_strSelect);
		}

		virtual std::vector<VRString> GetEnums(void) 
		{
			std::vector<VRString> listStr;
			for (std::vector<EnumType<ValueType> >::const_iterator cstItor = m_listValueType.begin(); \
				m_listValueType.end() != cstItor; ++cstItor)
			{
				listStr.push_back((*cstItor).m_strName);
			}

			return (listStr);
		}

	public:
		template<class T>
		struct EnumType 
		{
			VRString m_strName;
			T m_valueType;

			EnumType(const VRString& strName, T valueType)
			{
				m_strName = strName;
				m_valueType = valueType;
			}
			EnumType()
			{
				m_strName = "";
			}

			bool operator==(const VRString strName)
			{
				return (0 == m_strName.compare(strName));
			}
		};

	private:
		Container* m_cObject;//-- Pointer to the module that contain the property --
		void (Container::*ConstRefSet)(const ValueType& value);//-- Pointer to set member function --
		void (Container::*ConstSet)(const ValueType value);//-- Pointer to set member function --
		void (Container::*Set)(ValueType value);//-- Pointer to set member function --
		ValueType& (Container::*ConstRefGet)() const;//-- Pointer to get member function --
		ValueType (Container::*ConstGet)() const;//-- Pointer to get member function --
		ValueType (Container::*Get)();//-- Pointer to get member function --

		// 枚举值
		std::vector<EnumType<ValueType> > m_listValueType;
		VRString m_strSelect;
	};

#define DECLARE_PROPERTY(CLASSNAME, VALUETYPE, PROPERTYNAME)	\
public: CProperty<CLASSNAME, VALUETYPE> m_auto##PROPERTYNAME;

#define DEFINITION_PROPERTY(PROPERTYNAME, SETTRE, GETTER, STRITEMNAME, STRTEXT, STRUNTIL, CONTRL)  \
	m_auto##PROPERTYNAME.setContainer(this);	\
	m_auto##PROPERTYNAME.setter(SETTRE);	\
	m_auto##PROPERTYNAME.getter(GETTER);	\
	IAttributeItem* pI##PROPERTYNAME##Attribute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, STRITEMNAME, STRTEXT, STRUNTIL, &m_auto##PROPERTYNAME, true, CONTRL); \
	AddAttrItem(pI##PROPERTYNAME##Attribute);

#define ADDENUM_PROPERTY(PROPERTYNAME, STRTEXT, ENUMVALUE)  \
	m_auto##PROPERTYNAME.AddEnum(STRTEXT,ENUMVALUE);	
}

#endif // _PUBLIC_PROPERTYIMP_H_