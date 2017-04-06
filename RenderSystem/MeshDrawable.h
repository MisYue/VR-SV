/************************************************************************
 作者： LJ                                                            
 用途:  三维实体文件				                                        
 时间： 2015-12-29                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _MESHDRAWABLE_H_
#define _MESHDRAWABLE_H_

#pragma once

namespace VR_Soft
{
	class CMeshDrawable //: public CDrawableImp<IMeshDrawable>
	{
	public:
		CMeshDrawable(void);
		~CMeshDrawable(void);

	public:
		// 渲染函数
		virtual void OnDraw(void);
		// 初始化
		virtual void Init(void);
		// 设置名称
		virtual void SetMesh(const VRString& strMesh);

	private:
		VRString m_strMesh;

	};
}


#endif // !_MESHDRAWABLE_H_