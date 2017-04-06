/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体运动属性接口类	                                        */
/* 时间： 2016-06-8	                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IENTITYMOVETTRIBUTE_H_
#define _PUBLICE_IENTITYMOVETTRIBUTE_H_

namespace VR_Soft
{
	class IPath;

	class VRSOFT_DLL IEntityMoveAttribute : public IAttribute
	{
	public:
		// 析构函数
		virtual ~IEntityMoveAttribute(void) { }
		// 初始化开始的值 // 将模型朝向目标位置
		virtual void InitMove(void) = 0;
		// 设置实体速度
		virtual void SetVelocity(const double dVelocity) = 0;
		// 获得实体速度
		virtual double GetVelocity(void) const = 0;
		// 设置最大速度
		virtual void SetMaxVelocity(const double vVelocity) = 0;
		// 获得最大速度
		virtual double GetMaxVelocity(void) const = 0;
		// 设置加速度
		virtual void SetAcceleration(const double vAcceleration) = 0;
		// 获得加速度
		virtual double GetAcceleration(void) const = 0;
		// 设置目标位置
		virtual void SetTragetPosition(const osg::Vec3d& vPos) = 0;
		// 获得目标位置
		virtual osg::Vec3d GetTragetPosition(void) const = 0;
		// 设置当前索引位置
		virtual void SetIndex(const int index) = 0;
		// 获得当前索引位置
		virtual int GetIndex(void) const = 0;
		// 设置路径
		virtual void SetMovePath(IPath* pIPath) = 0;
		// 获得路径
		virtual IPath* GetMovePath(void) const = 0;
	};
}

#endif // !_PUBLICE_IENTITYMOVETTRIBUTE_H_