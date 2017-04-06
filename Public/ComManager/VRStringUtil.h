/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �ַ���������Ԫ		                                        */
/* ʱ�䣺 2016-07-09                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_VRSTRINGUTIL_H_
#define _PUBLIC_VRSTRINGUTIL_H_

#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	class VRSOFT_DLL CVRStringUtil
	{
	public: 
		// ���캯��
		explicit CVRStringUtil(void);
		// ��������
		virtual ~CVRStringUtil();
		// �ַ���ת��������
		template <typename T>
		static T StringToNumber(const VRString& str)
		{
			try
			{
				T value =  boost::lexical_cast<T>(str.c_str());
				return (value);
			}
			catch (...)
			{
				const VRString strTypeName(typeid(T).name());
				IComManager::GetInstance().WriteLogMsg("�ַ�����������ת��" + strTypeName + "ʧ��;StringToNumber", ERROR_CONVER_FAILD);

			}	

			return (T());
		}
		// ץ����д
		static VRString ToUpper( VRString& strText );
		// ת��Сд
		static VRString ToLower( VRString& strText );
		// Unicodeת��UTF8����
		static std::string UnicodeToUTF8(const std::wstring &src);
		// GB2312ת��Unicode����
		static std::wstring GB2312ToUnicode(const std::string& src);
		// GB2312ת��UTF8
		static std::string GB2312ToUTF8(const std::string& src);
	};
}

#endif // !_PUBLIC_VRSTRINGUTIL_H_