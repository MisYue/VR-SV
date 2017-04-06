/************************************************************************
 作者： LJ                                                            
 用途:  物理实体基类				                                        
 时间： 2015-12-29                                                    
 修改时间:                                                            
/************************************************************************/
#ifndef _PUBLIC_IMESHDRAWABLE_H_
#define _PUBLIC_IMESHDRAWABLE_H_

namespace VR_Soft
{
	class IMeshDrawAttribute : public IDrawAttribute
	{
	public: 
		// 析构函数
		virtual ~IMeshDrawAttribute() { }
		// 设置路径
		virtual void SetMeshPath(const VRString& strMeshPath) = 0;
		// 获得路径
		virtual VRString GetMeshPath(void) = 0;
		// 设置渲染体
		virtual void SetDrawObj(DrawObj* pDrawObj) = 0;
	};
}

#endif