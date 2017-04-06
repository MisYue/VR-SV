/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ��������													*/
/* ʱ�䣺 2015-09-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _TIMECONFIG_H_
#define _TIMECONFIG_H_

#pragma once

namespace VR_Soft
{
	class CTimeConfig : public IConfig
	{
	public:
		// ���캯��
		explicit CTimeConfig(void);
		// ��������
		virtual ~CTimeConfig(void);

	public:
		// ��ÿ�ʼʱ��
		bool GetInitTime(struct tm& t);
		// ��ü��ٱ���
		float GetMultipeTime(void);
		// ��ü���
		float GetQuicken(void);
		// ��ü���
		float GetModerate(void);

	public:
		// ���������ļ�
		virtual void SetConfigFile(const VRString& strfile) ;
		// �����ļ�
		virtual bool SaveConfigFile(void);

	protected:
		// String ת Int
		int ConvertFrom(const VRString& str);

	private:
		IConfigFile* m_pIConfig; // ���ò����ļ�
	};
}

#endif // _TIMECONFIG_H_
