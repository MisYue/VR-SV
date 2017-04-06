/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ��άʵ���ļ�				                                        
 ʱ�䣺 2015-12-29                                                    
 �޸�ʱ��:                                                            
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
		// ��Ⱦ����
		virtual void OnDraw(void);
		// ��ʼ��
		virtual void Init(void);
		// ��������
		virtual void SetMesh(const VRString& strMesh);

	private:
		VRString m_strMesh;

	};
}


#endif // !_MESHDRAWABLE_H_