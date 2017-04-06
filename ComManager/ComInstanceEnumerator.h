/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  插件实例管理类                                                */
/* 时间： 2015-05-14                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _CCOMINSTANCEENUMERATOR_H_
#define _CCOMINSTANCEENUMERATOR_H_

#pragma once

namespace VR_Soft
{
	class CComInstanceEnumerator : public IComInstanceMerator
	{
	public:
		// 构造函数
		explicit CComInstanceEnumerator(void);
		// 析构函数
		virtual ~CComInstanceEnumerator(void);
		// 添加工厂
		virtual void AddFactory(IComFactory* pIComFactory);
		// 删除工厂
		virtual void RemoveFactory(IComFactory* pIComFactory);

	public:
		// 创建插件
		virtual IComManagerFace* CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName);
		// 获得插件实例
		virtual IComManagerFace* GetComInstance(const VRString& strInstane) const;

	protected:
		typedef std::map<VRString, IComManagerFace*> MapStrInstance;
		typedef std::list<IComFactory*> ComFactoryList;

	private:
		MapStrInstance m_mapStrInstance; // 实例集合
		ComFactoryList m_comFactorys; // 工厂列表
		unsigned long m_nInstanceCreateCount; // 插件计数器

		VR_AUTO_MUTEX
	};
}


#endif // _CCOMINSTANCEENUMERATOR_H_

