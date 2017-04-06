#define VRSOFT_TOOLCLASS_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ToolClass/DyLib.h"

#if defined ( __WIN32__ ) || defined( _WIN32 )
#  define WIN32_LEAN_AND_MEAN
#  if !defined(NOMINMAX) && defined(_MSC_VER)
#   define NOMINMAX // required to stop windows.h messing up std::min
#  endif
#  include <windows.h>
#else 
#include <dlfcn.h>
#endif


namespace VR_Soft
{
	CDyLib::CDyLib(const VRString& fileName):m_strName(fileName)
	{
	}


	CDyLib::~CDyLib(void)
	{
	}

	// ��ô�����Ϣ
	VRString CDyLib::GetDyLibLastError(void)
	{
#if defined( __WIN32__ ) || defined( _WIN32 )
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0,
			NULL
			);
		VRString ret = (char*)lpMsgBuf;
		// Free the buffer.
		LocalFree( lpMsgBuf );
		return ret;
#else
		return VRString(dlerror());
#endif
	}

	// �����ļ�
	void CDyLib::Load(void)
	{
		IComManager::GetInstance().WriteLogMsg("���ز��" + m_strName);
		VRString strName = m_strName;
		// �ж��Ƿ�Ϊwindows����ϵͳ
#if defined( __WIN32__ ) || defined( _WIN32 )
		if (strName.substr(strName.length() - 4, 4) != ".dll")
		{
			strName += ".dll";
		}
#elif defined linux
		if (strName.find(".so") == String::npos)
			strName += ".so";
#else
		if (strName.substr(name.length() - 6, 6) != ".dylib")
			strName += ".dylib";
#endif

		// ���붯̬��
		m_hInstance = (DYNLIB_HANDLE)DYNLIB_LOAD(strName.c_str());
		if (NULL == m_hInstance)
		{
			IComManager::GetInstance().WriteLogMsg("���ز��" + m_strName + "ʧ��", ERROR_NOT_FIND);
			throw ERROR_EXCEPT;
		}

		IComManager::GetInstance().WriteLogMsg("�ɹ����ز��" + m_strName );
	}

	// ж���ļ�
	void CDyLib::Unload(void)
	{
		IComManager::GetInstance().WriteLogMsg("ж�ز��" + m_strName);
		// ж��
		if (DYNLIB_UNLOAD(m_hInstance))
		{
			IComManager::GetInstance().WriteLogMsg("ж�ز��" + m_strName + "ʧ��");
			throw ERROR_EXCEPT;
		}

		IComManager::GetInstance().WriteLogMsg("�ɹ����ز��" + m_strName );
	}

	void* CDyLib::GetSymbol( const VRString& strName ) const throw()
	{
		return (void*)DYNLIB_GETSYM( m_hInstance, strName.c_str() );
	}
}
