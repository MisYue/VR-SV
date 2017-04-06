/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  插件实例管理类接口                                            */
/* 时间： 2015-05-14                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ICOMINSTANCEENUMERATOR_H_
#define _ICOMINSTANCEENUMERATOR_H_

namespace VR_Soft
{
	class VRSOFT_DLL IComInstanceMerator : public CSingleton<IComInstanceMerator>
	{
	public:
		// 析构函数
		virtual ~IComInstanceMerator(void) { }
		// 创建插件
		virtual IComManagerFace* CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName) = 0;
		// 获得插件实例
		virtual IComManagerFace* GetComInstance(const VRString& strInstane) const = 0;
		// 添加工厂
		virtual void AddFactory(IComFactory* pIComFactory) = 0;
		// 删除工厂
		virtual void RemoveFactory(IComFactory* pIComFactory) = 0;
	};
}


#endif // _ICOMINSTANCEENUMERATOR_H_