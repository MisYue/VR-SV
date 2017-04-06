/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  配置头文件，负责系统疾病配置                                  */
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _VRCONFIG_H_
#define _VRCONFIG_H_

#include <string>
#include <boost/any.hpp>

#if defined( __WIN32__ ) || defined( _WIN32 )

#	define _VRSOFT_EXPORT_ __declspec( dllexport )
#	define _VRSOFT_IMPORT_ __declspec( dllimport )

#elif defined(__ARMCC__) || defined(__CC_ARM)

#	define _VRSOFT_EXPORT_ __attribute__ ((visibility("default")))
#	define _VRSOFT_IMPORT_ __attribute__ ((visibility("default")))

#endif

// 定义导出接口
#ifdef __cplusplus
#define  EXTERN_CPP extern "C"
#else
#define EXTERN_CPP extern
#endif

# define VRSOFT_DLL_EXPORT _VRSOFT_EXPORT_
# define VRSOFT_DLL_IMPORT _VRSOFT_IMPORT_

// 系统导入导出
#if defined(VRSOFT_EXPORT)
# define VRSOFT_DLL VRSOFT_DLL_EXPORT
#else
# define VRSOFT_DLL VRSOFT_DLL_IMPORT
#endif

// 插件导入导出
#if defined(VRSOFT_PLUGIN_EXPORT)
# define VRSOFT_PLUGIN_DLL VRSOFT_DLL_EXPORT
#else
# define VRSOFT_PLUGIN_DLL VRSOFT_DLL_IMPORT
#endif

#define OSG 1
#define OSGEARTH 1

#if defined(OSG) || defined(OSGEARTH)

#include <osg/Vec3>
#include <osg/Vec3d>
#include <osg/AutoTransform>
#include <osg/AlphaFunc>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/Image>
#include <osgGA/CameraManipulator>
#include <osgEarth/MapNode>

#define DrawObj osg::Node
#define EarthMap osgEarth::MapNode

#endif // OSG || OSGEARTH


namespace VR_Soft
{

	// 定义字符串名称
#ifdef UNICODE_
	typedef std::wstring _StringBase;
	typedef wchar_t VRChar;
#else
	typedef std::string _StringBase;
	typedef char VRChar;
#endif

#ifdef UNICODE_
	typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _StringStreamBase;
#else
	typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
#endif

	typedef _StringBase VRString;
	typedef _StringStreamBase VRStringStream;
	typedef VRStringStream stringstream;

	// 定义类型
	typedef unsigned int UINT;

#if defined(_MSC_VER)
	typedef __int64 Timer_t;
#else
	typedef unsigned long long Timer_t;
#endif

	// 宏定义

	// 属性设置获取宏接口
#define SET_GET_PROPERTY_INTERFACE(property, type) \
	virtual void Set##property(type property) = 0;\
	virtual type Get##property(void) const = 0;

	// 属性设置获取宏
#define SET_GET_PROPERTY(property, type, middle) \
	virtual void Set##property(type property){  m_##middle##property = property;}\
	virtual type Get##property(void) const {  return (m_##middle##property);} 
	// 设置属性
#define SET_PROPERTY(property, type, middle) inline void Set##property(type property){ VR_MUTEX_AUTO; m_##middle##property = property;}
	// 返回属性
#define GET_PROPERTY(property, type, middle) inline type Get##property(void) const { VR_MUTEX_AUTO; return (m_##middle##property);} 

	// 删除内存管理
#ifdef _DEBUG
#define VRSOFT_DELETE(p) if (NULL != p) {delete p; p = NULL;}
#define VRSOFT_DELETE_ARRAY(p) if (NULL != p) {delete[] p; p = NULL;}
#else
#define VRSOFT_DELETE(p) if (NULL != p) {delete p;  p = NULL;}
#define VRSOFT_DELETE_ARRAY(p) if (NULL != p) {delete[] p;  p = NULL;}
#endif

	// 设置位运算
#define SET_BIT(word, bit) (word |= bit);
#define SET_UNBIT(word, bit) (word &= ~bit);

	template <typename T> static inline T *GetPtrHelper(T *ptr) { return ptr; }
	template <typename Wrapper> static inline typename Wrapper::pointer GetPtrHelper(const Wrapper &p) { return p.data(); }

	// 申明类对象中的关联对象
#define DECLARE_PRIVATE(Class) \
	inline Class##Private* GetFunc() { return reinterpret_cast<Class##Private *>(GetPtrHelper(m_pPtr)); } \
	inline const Class##Private* GetFunc() const { return reinterpret_cast<const Class##Private *>(GetPtrHelper(m_pPtr)); } \
	friend class Class##Private;

#define DECLARE_PRIVATE_D(Dptr, Class) \
	inline Class##Private* GetFunc() { return reinterpret_cast<Class##Private *>(Dptr); } \
	inline const Class##Private* GetFunc() const { return reinterpret_cast<const Class##Private *>(Dptr); } \
	friend class Class##Private;

	// 申明类对象中的关联对象
#define DECLARE_PUBLIC(Class)                                    \
	inline Class* GetFunc() { return static_cast<Class *>(m_pPtr); } \
	inline const Class* GetFunc() const { return static_cast<const Class *>(m_pPtr); } \
	friend class Class;

	// 禁用拷贝函数和赋值函数
#define DISABLE_COPY(Class) \
private: \
	Class(const Class &); \
	Class &operator=(const Class &);

	typedef boost::any VRVariant;

	// 类型
	typedef std::vector<VRString> ListString;

}

#endif