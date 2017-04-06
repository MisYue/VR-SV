/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �����������ʵ����                                            */
/* ʱ�䣺 2015-07-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#pragma once

namespace VR_Soft
{
	class CComManagerConfig : public IComManagerConfig
	{
	public:
		explicit CComManagerConfig(const VRString& strPath);
		virtual ~CComManagerConfig(void);

	public: 
		// ��ӵ�ǰ����ӵ����
		void AddComName(const VRString& strComName );
		// �Ƴ���ǰ����ӵ����
		void RemoveComName(const VRString& strComName);
		// ���浱ǰ�Ѿ���ӵ�����
		void Sava(void);
		// ��ȡ����ӵĲ������
		void ReadCom(void);

	public:
		// ��ʼ������ϵͳ
		virtual void Init() ;
		// ���ִ��·��
		virtual VRString GetCurPath(void) const;

	protected:
		// ���ȫ��·��
		VRString GetExePath(void) const;
		void Replace(char* szLine);
	protected:
		typedef std::vector<VRString> LstLoadedCom; // �����Ѿ����ص����

	private:
		VRString m_strPath; // ��ִ�г������ڵ�·��
		mutable VRString m_strCurPath; // ��ǰ��·��

		LstLoadedCom m_lstLoadedCom; // ��ǰ���ص�·������

		VR_AUTO_MUTEX
	};
}


