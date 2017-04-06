/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染属性接口类	                                        */
/* 时间： 2016-08-10                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYDRAWATTRIBUTE_H_
#define _PUBLIC_IENTITYDRAWATTRIBUTE_H_

namespace VR_Soft
{
	class IEntityDrawAttribute : public IAttribute
	{
	public: 
		enum DrawModel
		{
			DM_3D,		// 三维模式
			DM_2D,		// 二维模式
			DM_2D_3D	// 二维三维模式
		};

	public: 
		// 析构函数
		virtual ~IEntityDrawAttribute(void) { }
		// 设置位置
		virtual void SetPosition(const osg::Vec3d& vPos) = 0;
		// 获得位置
		virtual osg::Vec3d GetPosition(void) const = 0;
		// 设置缩放
		virtual void SetScale(const osg::Vec3d& vScale) = 0;
		// 获得缩放
		virtual osg::Vec3d GetScale(void) const = 0;
		// 设置旋转
		virtual void SetRotate(const osg::Vec3d& vRot) = 0;
		// 获得旋转
		virtual osg::Vec3d GetRotate(void) const = 0;
		// 设置显示模式
		virtual void SetDrawModel(const DrawModel dm) = 0;
		// 获得显示模式
		virtual DrawModel GetDrawModel(void) const = 0;
		// 设置二维显示图片
		virtual void SetEntity2D(const VRString& strFile) = 0;
		// 获得二维显示图片
		virtual VRString GetEntity2D(void) const = 0;
		// 是否改变当前的二维图片
		virtual bool ChangeEntity2D(void) const = 0;
	};
}

#endif // ! _PUBLIC_IENTITYDRAWATTRIBUTE_H_