/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  单例基类 模板头文件                                           */
/* 时间： 2015-05-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef SINGLETMP_H
#define SINGLETMP_H

namespace VR_Soft
{
	template <typename T>
	class CSingleton
	{
	public:
		// 构造函数
		explicit CSingleton(void)
		{
			// 断言确认 对象为空
			assert(m_pSingleton == NULL);

#if defined(_MSC_VER) && _MSC_VER < 1200
			// 计算地址对象
			int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
			m_pSingleton = (T*)((int)this + offset);
#else
			m_pSingleton = static_cast<T*>(this);
#endif
		}
		// 析构函数
		~CSingleton(void)
		{
			// 断言指针不为空
			assert (m_pSingleton != NULL);
			m_pSingleton = NULL;
		}

	public:
		// 获取单例对象
		static T* GetInstancePtr(void)
		{
			return (m_pSingleton);
		}

		static T& GetInstance(void)
		{
			//断言指针不为空
			assert(NULL != m_pSingleton);
			return (*m_pSingleton);
		}

	protected:
		static T* m_pSingleton; // 单例对象

	private:
		// 禁止= 和 拷贝函数
		CSingleton(const CSingleton<T>& );
		CSingleton& operator=(const CSingleton<T>& );
	};

	template<typename T>
	T* CSingleton<T>::m_pSingleton = NULL;
}

#endif // SINGLETMP_H