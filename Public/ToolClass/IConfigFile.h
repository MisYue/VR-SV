/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ӿ�		                                        */
/* ʱ�䣺 2015-05-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ICONFIGFILE_H_
#define _ICONFIGFILE_H_

namespace VR_Soft
{
	class VRSOFT_DLL IConfigFile
	{
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
		// ��ȡ�ļ�
		virtual void ReadConfig(void) = 0;
	};

	// �������ö���
	EXTERN_CPP VRSOFT_TOOLCLASS_DLL IConfigFile* CreateConfigFileInstance(const VRString& strConfigFile);
}

#endif // _ICONFIGFILE_H_