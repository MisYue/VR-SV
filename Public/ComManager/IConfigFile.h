/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ӿ�		                                        */
/* ʱ�䣺 2015-05-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ICONFIGFILE_H_
#define _ICONFIGFILE_H_

#include <list>

namespace VR_Soft
{
	typedef struct ITEMVALUE_TYP
	{
		VRString strItem; // ������
		VRString strValue; // ֵ

		ITEMVALUE_TYP(VRString item, VRString value):strItem(item),strValue(value)
		{

		}

		bool operator== (const VRString item)
		{
			return (strItem.compare(item) == 0);
		}

		bool operator== (const VRString item) const
		{
			return (strItem.compare(item) == 0);
		}
	}ITEMVALUE, *PTR_ITEMVALUE;

	class VRSOFT_DLL IConfigFile
	{
	public:
		typedef std::list<ITEMVALUE> LstItemValue;
	public:
		// ��������
		virtual ~IConfigFile() { }
		// �������ļ�
		virtual bool OpenFile(void) = 0;
		// �������ļ�
		virtual bool OpenFile(const VRString& strFile) = 0;
		// �ر��ļ�
		virtual void CloseFile(void) = 0;
		// ��ȡ�ļ����ƶ�Ӧ���ֵ
		virtual VRString GetItemValue(const VRString& strName, const VRString& strItem) const = 0;
		// ���һ�����µ�������Ŀ
		virtual const LstItemValue& GetItemValus(const VRString& strName) const = 0;
		// ��ȡ�ļ�
		virtual void ReadConfig(void) = 0;
	};

	// �������ö���
	EXTERN_CPP VRSOFT_DLL IConfigFile* CreateConfigFileInstance(const VRString& strConfigFile);
}

#endif // _ICONFIGFILE_H_