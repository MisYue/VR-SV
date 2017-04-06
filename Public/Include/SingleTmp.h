/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������� ģ��ͷ�ļ�                                           */
/* ʱ�䣺 2015-05-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef SINGLETMP_H
#define SINGLETMP_H

namespace VR_Soft
{
	template <typename T>
	class CSingleton
	{
	public:
		// ���캯��
		explicit CSingleton(void)
		{
			// ����ȷ�� ����Ϊ��
			assert(m_pSingleton == NULL);

#if defined(_MSC_VER) && _MSC_VER < 1200
			// �����ַ����
			int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
			m_pSingleton = (T*)((int)this + offset);
#else
			m_pSingleton = static_cast<T*>(this);
#endif
		}
		// ��������
		~CSingleton(void)
		{
			// ����ָ�벻Ϊ��
			assert (m_pSingleton != NULL);
			m_pSingleton = NULL;
		}

	public:
		// ��ȡ��������
		static T* GetInstancePtr(void)
		{
			return (m_pSingleton);
		}

		static T& GetInstance(void)
		{
			//����ָ�벻Ϊ��
			assert(NULL != m_pSingleton);
			return (*m_pSingleton);
		}

	protected:
		static T* m_pSingleton; // ��������

	private:
		// ��ֹ= �� ��������
		CSingleton(const CSingleton<T>& );
		CSingleton& operator=(const CSingleton<T>& );
	};

	template<typename T>
	T* CSingleton<T>::m_pSingleton = NULL;
}

#endif // SINGLETMP_H