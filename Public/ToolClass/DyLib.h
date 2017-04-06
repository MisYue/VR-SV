/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  动态库加载                                                    */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLICE_DYLIB_H_
#define _PUBLICE_DYLIB_H_

#pragma once


#if ( __WIN32__ ) || defined( _WIN32 )
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibraryExA( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#else OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID || OGRE_PLATFORM == OGRE_PLATFORM_NACL
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )
#endif

namespace VR_Soft
{
	class VRSOFT_TOOLCLASS_DLL CDyLib
	{
	public:
		// 动态库
		explicit CDyLib(const VRString& fileName);
		~CDyLib(void);

		// 载入文件
		void Load(void);
		// 卸载文件
		void Unload(void);
		// 获取动态库名称
		const VRString& GetName(void) const { return (m_strName); }

		
        /**
            Returns the address of the given symbol from the loaded library.
            @param
                strName The name of the symbol to search for
            @return
                If the function succeeds, the returned value is a handle to
                the symbol.
            @par
                If the function fails, the returned value is <b>NULL</b>.

        */
		void* GetSymbol(const VRString& strName) const throw();

	protected:
		CDyLib(const CDyLib&);
		CDyLib& operator= (const CDyLib&);
		bool operator==(const CDyLib&);

	protected:
		// 获得错误信息
		VRString GetDyLibLastError(void);

	private:
		VRString m_strName; // 动态库文件名称
		DYNLIB_HANDLE m_hInstance; // 动态库句柄
	};
}

#endif // _PUBLICE_DYLIB_H_


