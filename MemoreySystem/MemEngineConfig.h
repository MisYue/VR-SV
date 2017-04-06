/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �ڴ�����������												*/
/* ʱ�䣺 2015-11-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef  _MEMENGINECONFIGE_H_
#define  _MEMENGINECONFIGE_H_

#pragma once

namespace VR_Soft
{
	class CMemEngineConfig : public IConfig
	{
	public:
		explicit CMemEngineConfig(void);
		virtual ~CMemEngineConfig(void);

	public:
		// ���������ļ�
		virtual void SetConfigFile(const VRString& strfile);
		// �����ļ�
		virtual bool SaveConfigFile(void);

	public:
		// �����Ҫ����Ŀռ��С
		int GetMenCount(void) const;
		// �����ʼ��ַ
		int GetStartAddr(void) const;
		// ������ݱ�ʶ��С
		int GetStructCount(void) const;

	protected:
		// ��ʼ��
		void Init(void);


	private:
		IConfigFile* m_pIConfig; // ���ò����ļ�
		int m_nCount; // �����ڴ��С
		int m_nStructCount; // ��ʽ����С
		int m_nStartAddr; // ��ʼ��ַ
	};
}

#endif // !_MEMENGINECONFIGE_H_