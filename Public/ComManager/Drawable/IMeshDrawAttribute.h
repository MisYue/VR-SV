/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ����ʵ�����				                                        
 ʱ�䣺 2015-12-29                                                    
 �޸�ʱ��:                                                            
/************************************************************************/
#ifndef _PUBLIC_IMESHDRAWABLE_H_
#define _PUBLIC_IMESHDRAWABLE_H_

namespace VR_Soft
{
	class IMeshDrawAttribute : public IDrawAttribute
	{
	public: 
		// ��������
		virtual ~IMeshDrawAttribute() { }
		// ����·��
		virtual void SetMeshPath(const VRString& strMeshPath) = 0;
		// ���·��
		virtual VRString GetMeshPath(void) = 0;
		// ������Ⱦ��
		virtual void SetDrawObj(DrawObj* pDrawObj) = 0;
	};
}

#endif