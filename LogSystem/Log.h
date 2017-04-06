/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־����				                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_

#pragma once

#include <fstream>

namespace VR_Soft
{
	class CLog : public ILog
	{
	public:
		explicit CLog(const VRString& strName, bool bDebugOut = false, bool bSupperFile = true);
		virtual ~CLog(void);

		// �������
		const VRString& GetName(void) const { return (m_strName); }
		// ��־��Ϣ
		void SetLogMessage(const VRString& strLog, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false);
		// ��ȡ������Ϣ
		const VRString& GetErrorMessage(void) const;
		// ��ȡ�Ƿ��ļ�֧������
		bool IsDebugOut(void) const;
		// ��ȡ�Ƿ�֧���ļ�����
		bool IsSupperFile(void) const;
		// ��ȡ�Ƿ�֧��ʱ��
		bool IsTimeStampEnabled(void) const;
		// ���ô�����
		SET_GET_PROPERTY(Code, UINT, ui);


	private:
		bool m_bDebugOut; // �������������̨����
		bool m_bSupperFile; //�Ƿ�֧��
		bool m_bSupperTime; // ʹ��ʱ��
		VRString m_strName; // ��־�ļ�
		std::ofstream m_fstrLog; // ϵͳ�ļ�
		VRString m_strLastLog; // ��ȡ����
		UINT m_uiCode; // ������

		VR_AUTO_MUTEX
	};
}

#endif