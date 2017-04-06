/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������													*/
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _EARTHCONFIG_H_
#define _EARTHCONFIG_H_

#pragma once

namespace VR_Soft
{
	class CEarthConfig : public IConfig
	{
	public:
		// ���캯��
		explicit CEarthConfig(const VRString& strFile);
		// ��������
		virtual ~CEarthConfig(void);

	public:
		// ���������ļ�
		virtual void SetConfigFile(const VRString& strfile) ;
		// �����ļ�
		virtual bool SaveConfigFile(void) ;

	private:
		IConfigFile* m_pIConfig; // ���ò����ļ�
	};
}


#endif //  _EARTHCONFIG_H_