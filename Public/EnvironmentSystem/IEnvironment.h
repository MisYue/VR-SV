/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备接口														*/
/* 时间： 2015-11-24                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENVIRONMENT_H_
#define _PUBLIC_IENVIRONMENT_H_

namespace VR_Soft
{
	class IEnvironment : public CEntityBaseImp<IEntityRenderBase>
	{
	public:
		// 析构函数
		virtual ~IEnvironment(void) { }
	};

	// 创建雷达对象工厂
	CREATE_ENTITYBASE_FACTORY(CreateEnvironmentFactory);
}

#endif // !_PUBLIC_IENVIRONMENT_H_