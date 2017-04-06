/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ʵ����			                                        */
/* ʱ�䣺 2015-05-27                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _TRACKSLINE_H_
#define _TRACKSLINE_H_

#pragma once

#include <osg/LineWidth>
#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	class CTracksLine : public CAttributeImp<IDrawAttribute>
	{
	public:
		// ���캯��
		explicit CTracksLine(IEntityBase* pIEntityBase); 
		// ��������
		virtual ~CTracksLine(void);

	public:
		// ��ʼ��
		virtual void Init();
		// ����
		virtual void Update(void);
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);
		// �Ƿ������ƶ�
		virtual bool IsMove(void) const ;

	public:
		// �����Ƿ�����
		void SetShow(bool bShow) ;
		// ����Ƿ�����
		bool GetShow(void) const;
		// �����߿�
		void SetLineWidth(int nWidth);
		// ����߿�
		int GetLineWidth(void) const;
		// �Ƿ�򿪹���
		void SetLightOn(bool bOn);
		// ��ù���״̬
		bool IsOpenLight(void) const;

	public:
		// ����
		//AutoProperty(osg::Vec3d, Postion);
		DECLARE_PROPERTY(CTracksLine, bool, Show);
		DECLARE_PROPERTY(CTracksLine, int, LineWidth);
		DECLARE_PROPERTY(CTracksLine, bool, Light);


	protected:
		// ��ӵ�������Ⱦ����
		void AddPoint(const osg::Vec3f& vWorld);
		// ������Ⱦ��
		void UpdateGeomerty(void);

	private:
		osg::Geode* m_pGeode; // ��Ⱦ�ڵ�
		osg::Geometry* m_pGeomerty; // ��Ⱦ��

		int m_nMaxCount; // ��Ⱦ����������
		bool m_bShow; // �Ƿ���ʾ
		int n_nCurrent; // ��ǰ����
		osg::LineWidth* m_pLineWidth; // �߿�
		bool m_bOpenLight; // �Ƿ�򿪹���
	};
}


#endif // !_TRACKSLINE_H_