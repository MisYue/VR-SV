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

	// 获得错误信息
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

	// 载入文件
	void CDyLib::Load(void)
	{
		IComManager::GetInstance().WriteLogMsg("加载插件" + m_strName);
		VRString strName = m_strName;
		// 判断是否为windows操作系统
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

		// 导入动态库
		m_hInstance = (DYNLIB_HANDLE)DYNLIB_LOAD(strName.c_str());
		if (NULL == m_hInstance)
		{
			IComManager::GetInstance().WriteLogMsg("加载插件" + m_strName + "失败", ERROR_NOT_FIND);
			throw ERROR_EXCEPT;
		}

		IComManager::GetInstance().WriteLogMsg("成功加载插件" + m_strName );
	}

	// 卸载文件
	void CDyLib::Unload(void)
	{
		IComManager::GetInstance().WriteLogMsg("卸载插件" + m_strName);
		// 卸载
		if (DYNLIB_UNLOAD(m_hInstance))
		{
			IComManager::GetInstance().WriteLogMsg("卸载插件" + m_strName + "失败");
			throw ERROR_EXCEPT;
		}

		IComManager::GetInstance().WriteLogMsg("成功加载插件" + m_strName );
	}

	void* CDyLib::GetSymbol( const VRString& strName ) const throw()
	{
		return (void*)DYNLIB_GETSYM( m_hInstance, strName.c_str() );
	}
}
