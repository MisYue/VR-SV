/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ̧ͷHUD��Ļ
 ʱ�䣺 2015-11-28                                                    
 �޸�ʱ��:                                                            
************************************************************************/
#ifndef _SCREENHUD_H_
#define _SCREENHUD_H_

#pragma once

#include <osg/Camera>

namespace osgText
{
	class Text;
}

namespace VR_Soft
{
	class CScreenHUD  : public osg::Camera, public IScreenHUD
	{
	public:
		CScreenHUD(const VRString& strName);
		// ��������
		virtual ~CScreenHUD(void);

	public: 
		// ���ô�������
		virtual void SetHUDName(const VRString& strName) ;
		// ��ô�������
		virtual const VRString& GetHUDName(void) const ;
		// �ƶ�λ��
		virtual void Move(int x, int y, int width, int height) ;
		// ��������
		virtual void SetText(const VRString& strText) ;
		// ���ñ�����ɫ
		virtual void SetBgColor(const float r, const float g, const float b, const float a = 1.0f) ;
		// ��ʾ
		virtual void Show(void) ;
		// ����
		virtual void Hide(void) ;
		// ��ʾ����״̬
		virtual bool ShowState(void) const {return m_bShow; }

	public:
		// ������С
		void OnResize(int width, int height);
		// ��������
		void UpdateText(void);

	protected:
		// ��ʼ��
		void Init(void);
		// test
		void Test();
		
	private:
		osgText::Text      *m_pText;
		osg::Group		   *m_pRoot;
		osg::Geode*			m_pBkGeode; // ����
		VRString			m_strText;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		bool m_bShow;
	};
}


#endif // !_SCREENHUD_H_